//
// Created by yyx on 2022/1/22.
//



#include "metadata_server.h"
#include "metadata_system.h"
#include "tools.h"
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void print(const string &message) {
    if (message.empty() || message.back()!='\n') {
        cout << message << endl;
        cout.flush();
    }
    else {
        cout << message;
        cout.flush();
    }
}


MetadataServer::MetadataServer(string self_ip, int self_port, string master_ip, int master_port, int slave_num)
        : self_ip_(move(self_ip)), self_port_(self_port), master_ip_(move(master_ip)), master_port_(master_port), slave_num_(slave_num) {
    is_master_ = (self_ip_ == master_ip_) && (self_port_ == master_port_);
    self_slave_id_ = -1;
    server_socket_ = nullptr;
    if (is_master_) {
        InitMaster();
    }
    else {
        InitSlave();
    }
}


void MetadataServer::WhichSlaveToStore(int file_id, vector<int>& slaves) const {
    if (slave_num_ == 2) {
        slaves.push_back(0);
        slaves.push_back(1);
    }
    else {
        for (int i = 0; i < ceil(slave_num_ / 3.0); ++i) {
            slaves.push_back((file_id + i) % slave_num_);
        }
    }
}

void MetadataServer::CheckSlaveStats(string& result) {
    stringstream message_stream;
    for (int i = 0; i < slave_num_; ++i) {
        string message = "WUP";
        string received_message;
        bool connected = client_sockets_[i]->SendMessage(message)
                         && client_sockets_[i]->GetMessage(received_message)
                         && received_message == "WUP";
        message_stream.str("");
        message_stream << GetSlaveInfoFromId(i) << " is" << (connected ? "" : " not") << " online.\n";
        result += message_stream.str();
    }
}

void MetadataServer::SendMessageToSlaveIp(const string& slave_ip, int slave_port, const string& message, string& result) {
    ClientSocket client_socket(slave_ip, slave_port);
    string line;
    if (!client_socket.SendMessage(message) || !client_socket.GetMessage(result)) {
        result = "Failure";
    }
}

void MetadataServer::SendMessageToSlaves(const vector<int>& slaves, const string& message, string& result) {
    vector<string> responses;
    stringstream message_stream;
    for (int slave_id : slaves) {
        string slave_info = GetSlaveInfoFromId(slave_id);
        string received_message;
        message_stream.str("");
        message_stream << "[Master] → " << slave_info << ": " << message;
        print(message_stream.str());
        if (!connection_stats_[slave_id] && !need_replacement_stats_[slave_id]) {
            responses.emplace_back("");
            message_stream.str("");
            message_stream << "Slave " << slave_id << slave_info << " is still dead\n";
            result += message_stream.str();
        }
        else if (need_replacement_stats_[slave_id]) {
            responses.emplace_back("");
            delete client_sockets_[slave_id];
            ConnectSlave(slave_id);
            if (!RecoverSlave(slave_id)) {
                message_stream.str("");
                message_stream << "Slave " << slave_id << slave_info << " recovery failed\n";
                result += message_stream.str();
                message_stream.str("");
                message_stream << "[Master] Failed to recover slave " << slave_info << ".";
                print(message_stream.str());
            }
            else {
                connection_stats_[slave_id] = true;
                need_replacement_stats_[slave_id] = false;
                message_stream.str("");
                message_stream << "Slave " << slave_id << slave_info << " finds a replacement\n";
                result += message_stream.str();
                message_stream.str("");
                message_stream << "[Master] Slave " << slave_info << " recovered.";
                print(message_stream.str());
            }
        }
        else if (client_sockets_[slave_id]->SendMessage(message) && client_sockets_[slave_id]->GetMessage(received_message)) {
            responses.push_back(received_message);
            message_stream.str("");
            message_stream << "[Slave] " << slave_info + ": " << (received_message == "Success" ? "" : "\n") << received_message + "\n";
            result += message_stream.str();
            message_stream.str("");
            message_stream << "[Master] ← " << slave_info << ": " << (received_message == "Success" ? "" : "\n")  << received_message;
            print(message_stream.str());
        }
        else {
            responses.emplace_back("");
            connection_stats_[slave_id] = false;
            message_stream.str("");
            message_stream << "[WARNING] Failed to connect to " << slave_info << ".";
            print(message_stream.str());
            message_stream.str("");
            message_stream << "Slave " << slave_id << slave_info << " has lost the contact.\n";
            result += message_stream.str();
        }
    }

    string final_output;
    for (int i = 0; i < slaves.size(); i++) {
        if (responses[i].empty()) {
            continue;
        }
        else {
            final_output = responses[i];
            vector<string> tokens;
            tokens = SplitString(responses[i]);
            if (tokens[0] != "[ERROR]") {
                break;
            }
        }
    }
    message_stream.str("");
    message_stream << "[Master]: " << (final_output == "Success" ? "" : "\n")  << final_output << "\n";
    result += message_stream.str();
}

void MetadataServer::Run() {
    SystemClass* inner_system;
    if (is_master_) {
        inner_system = new FileSystem(this);
    }
    else {
        inner_system = new MetadataSystem(this);
        MetadataSystem* temp_p = dynamic_cast<MetadataSystem *>(inner_system);
        temp_p->setPoolname(to_string(self_slave_id_));
        temp_p->InitKVengine();
    }
    Run(inner_system);
}

void MetadataServer::InitSlave() {
    stringstream message_stream;
    print("[Slave] Working as a slave server...");
    message_stream << "[Slave] Connecting to the master at " << master_ip_ << ":" << master_port_ << "...";
    print(message_stream.str());
    string message("port " + to_string(self_port_));
    for (int i = 0; i < 10; ++i) {
        ClientSocket test_connection(master_ip_, master_port_);
        string received_message;
        if (test_connection.SendMessage(message) && test_connection.GetMessage(received_message)) {
            vector<string> tokens;
            tokens = SplitString(received_message);
            if (tokens[0] == "[ERROR]") {
                Error("[Slave] Enough slaves in the system.");
            }
            self_slave_id_ = stoi(tokens[0]);
            self_ip_ = tokens[1];
            message_stream.str("");
            message_stream << "[Slave] Connected to the master as slave " << self_slave_id_ << ".";
            print(message_stream.str());
            break;
        }
    }
    if (self_slave_id_ == -1) {
        print("[Slave] Failed to connect to the master.");
        exit(0);
    }
    else {
        server_socket_ = new ServerSocket(self_port_);
        print("[Slave] Successfully initialized.");
    }
}

void MetadataServer::InitMaster() {
    stringstream message_stream;
    print("[Master] Working as the master server...");
    message_stream << "[Master] Waiting for " << slave_num_ << " slaves...";
    print(message_stream.str());
    server_socket_ = new ServerSocket(self_port_);
    for (int i = 0; i < slave_num_; ++i) {
        while (true) {
            server_socket_->connection();
            string message = to_string(i) + " " + server_socket_->GetClientAddr();
            string line;
            vector<string> argv;
            if (!(server_socket_->GetMessage(line) && server_socket_->SendMessage(message))) {
                continue;
            }
            else {
                vector<string> tokens = SplitString(line);
                if (tokens[0] != "port") {
                    continue;
                }
                else {
                    vector<string> slave_profile;
                    slave_profile.push_back(server_socket_->GetClientAddr());
                    slave_profile.push_back(tokens[1]);
                    slave_table_.push_back(slave_profile);
                    message_stream.str("");
                    message_stream << "[Master] Received message from slave " << i << " at " << slave_profile[0] << ":" << slave_profile[1] << ".";
                    print(message_stream.str());
                    break;
                }
            }
        }
    }
    for (int i = 0; i < slave_num_; ++i) {
        string ip = slave_table_[i][0];
        int port = stoi(slave_table_[i][1]);
        client_sockets_.push_back(new ClientSocket(ip, port));
        string message = "WUP";
        string received_message;
        while (true) {
            if (client_sockets_.back()->SendMessage(message) && client_sockets_.back()->GetMessage(received_message)) {
                break;
            }
            else {
                delete client_sockets_[i];
                client_sockets_[i] = new ClientSocket(ip, port);
            }
        }
        connection_stats_.push_back(true);
        need_replacement_stats_.push_back(false);
        message_stream.str("");
        message_stream << "[Master] Connected to " << ip << ":" << port << ".";
        print(message_stream.str());
    }
    print("[Master] Service online.");
}

string MetadataServer::GetSlaveInfoFromId(int slave_id) {
    stringstream message_stream;
    message_stream << "[" << slave_id << " at " << slave_table_[slave_id][0] << ":" << slave_table_[slave_id][1] << "]";
    return message_stream.str();
}

void MetadataServer::ConnectSlave(int slave_id) {
    string ip = slave_table_[slave_id][0];
    int port = stoi(slave_table_[slave_id][1]);
    client_sockets_[slave_id] = new ClientSocket(ip, port);
}

bool MetadataServer::SyncSlaves(int src_slave_id, int dst_slave_id) {
    string message = "pushto " + slave_table_[dst_slave_id][0] + ":" + slave_table_[dst_slave_id][1];
    vector<int> slave_ids;
    slave_ids.push_back(src_slave_id);
    string result;
    delete client_sockets_[dst_slave_id];
    SendMessageToSlaves(slave_ids, message, result);
    ConnectSlave(dst_slave_id);
    vector<string> messages;
    messages = SplitString(result, "\n");
    vector<string> words;
    words = SplitString(messages[1]);
    return words.size() == 3 && words[2] == "Success";
}

bool MetadataServer::RecoverSlave(int slave_id) {
    int count = 0;
    for (int i = 1; i < slave_num_; ++i) {
        int neighbour_id = (slave_id + 1) % slave_num_;
        if (connection_stats_[neighbour_id] && SyncSlaves(neighbour_id, slave_id)) {
            ++count;
            if (count >= 2) {
                break;
            }
        }
    }
    return (count >= 2) || ((count == 1) && slave_num_ == 2);
}

[[noreturn]] void MetadataServer::Run(SystemClass* inner_system) {
    server_socket_->connection();
    while (true) {
        string received_message;
        vector<string> argv;
        string message;
        if (!server_socket_->GetMessage(received_message)) {
            continue;
        }
        cout << "↓ ";
        print(received_message);

        argv = SplitString(received_message);
        inner_system->ExecuteCommand(argv, message);
        if(typeid(*(inner_system->GetClassType()))== typeid(FileSystem)){
            print("cache");
        }
        if (message.empty()) {
            message = "[EMPTY]";
        }
        if (!server_socket_->SendMessage(message)) {
            continue;
        }
        cout << "↑\n";
        print(message);
        cout << endl;
    }
}
