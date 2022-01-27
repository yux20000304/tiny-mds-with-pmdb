//
// Created by yyx on 2022/1/23.
//

#include "metadata_system.h"
#include "tools.h"
#include <string>
#include <string.h>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <libpmemkv.hpp>
#include <sstream>

#define ASSERT(expr)                                                                     \
	do {                                                                             \
		if (!(expr))                                                             \
			std::cout << pmemkv_errormsg() << std::endl;                     \
		assert(expr);                                                            \
	} while (0)
#define LOG(msg) std::cout << msg << std::endl

const uint64_t SIZE = 1024UL * 1024UL * 1024UL;

using namespace std;



MetadataSystem::MetadataSystem(MetadataServer* owner): metadata_map_(), owner_(owner) {
}

MetadataSystem::~MetadataSystem() {
    for (auto it = metadata_map_.begin(); it != metadata_map_.end(); it++) {
        delete it->second;
        metadata_map_.erase(it);
    }
    kv.close();
}

void MetadataSystem::wup(const vector<string> &args, string &feedback) {
    feedback = "WUP";
}

void MetadataSystem::pushto(const vector<string>& args, string& feedback) {
    feedback = "Success";
    string ip = args[1];
    int port = stoi(args[2]);
    for (auto & it : metadata_map_) {
        string result;
        string message = "create " + it.second->GetSummary();
        MetadataServer::SendMessageToSlaveIp(ip, port, message, result);
        if (result != "Success" && result != "[ERROR] File ID already exists.") {
            feedback = "Failure";
        }
    }
}

void MetadataSystem::ExecuteCommand(const vector<string>& command_args, string& feedback) {
    if (command_args.empty()) {
        Error("[ERROR] No command arguments received.\n");
    }
    const string& command = command_args[0];
    if (command == "WUP") {
        this->wup(command_args, feedback);
    }
    else if (command == "request") {
        this->request(command_args, feedback);
    }
    else if (command == "delete") {
        this->remove(command_args, feedback);
    }
    else if (command == "create") {
        this->create(command_args, feedback);
    }
    else if (command == "update") {
        this->update(command_args, feedback);
    }
    else if (command == "pushto") {
        this->pushto(command_args, feedback);
    }
    else {
        feedback = "[ERROR] Command " + command + " is not supported.\n";
    }
//    for (auto & tmp_node : metadata_map_) {
//        cout << tmp_node.second->GetInfo() << endl;
//    }
//    auto res_it = kv.new_read_iterator();
//    ASSERT(res_it.is_ok());
//    auto &it = res_it.get_value();
//    LOG("Iterate from first to last element");
//    s = it.seek_to_first();
//    ASSERT(s == pmem::kv::status::OK);
//    do{
//        auto key = (std::string)it.key().get_value().data();
//        LOG("OID = " + key);
//
//        auto value = (std::string)it.read_range().get_value().data();
//        LOG("Metadata = " + value );
//    }while (it.next() == pmem::kv::status::OK);
}

void MetadataSystem::request(const vector<string>& args, std::string& feedback) {
    if (args.size() != 2) {
        feedback = "[ERROR] Request require 1 argument.\n";
        return;
    }

//    int id = stoi(args[1]);
//    auto it = metadata_map_.find(id);
//    if (it == metadata_map_.end()) {
//        feedback = "[ERROR] Request failed.";
//        return;
//    }
    GetMetadataCache(const_cast<string &>(args[1]), feedback);
}

void MetadataSystem::remove(const vector<string>& args, std::string& feedback) {
    if (args.size() != 2) {
        feedback =  "[ERROR] Remove requires 1 argument.";
        return;
    }
//    int id = stoi(args[1]);
//    auto tmp = metadata_map_.find(id);
//    if (tmp == metadata_map_.end()) {
//        feedback =  "[ERROR] Remove failed.";
//        return;
//    }
//    delete tmp->second;
//    metadata_map_.erase(tmp);

    RemoveMetadataCache(const_cast<string &>(args[1]));
    feedback =  "Success";
}

void MetadataSystem::create(const vector<string>& args, std::string& feedback) {
    if (args.size() != 8) {
        feedback = "[ERROR] Create requires 7 arguments.";
        return;
    }
//    int id = stoi(args[1]);
//    int parent = stoi(args[2]);
//    const string& creation_time = args[3];
//    const string& lastmodify_time = args[4];
//    size_t size = stoi(args[5]);
//    const string& name = args[6];
//    const int type = stoi(args[7]);
//    auto* new_metadata = new MetadataNode(id, parent, creation_time, size, lastmodify_time, name, type);
//    auto tmp = metadata_map_.find(id);
//    if (tmp != metadata_map_.end()) {
//        feedback = "[ERROR] File ID already exists.";
//        return;
//    }
//    metadata_map_.insert(pair<int, MetadataNode*>(id, new_metadata));
    string temp = args[2] + " " + args[3] + " " + args[4] + " " + args[5] + " " + args[6] + " " + args[7];
    PutMetadataCache(const_cast<string &>(args[1]), temp);
    feedback = "Success";
    auto res_it = kv.new_read_iterator();
    ASSERT(res_it.is_ok());
    auto &it = res_it.get_value();
    LOG("Iterate from first to last element");
//    s = it.seek_to_first();
//    ASSERT(s == pmem::kv::status::OK);
    kv.get_all([](pmem::kv::string_view k, pmem::kv::string_view v) {
        LOG("  cache item : " << k.data() << " " << v.data());
        return 0;
    });
}

void MetadataSystem::update(const vector<string>& args, std::string& feedback)
{
    if ((args.size()) % 2 != 0) {
        feedback = "[ERROR] Wrong arguments for update.";
        return;
    }
    s = kv.exists(args[1]);
    ASSERT(s == pmem::kv::status::OK);

    string temp_value;
    string push_value = "";
    vector<string> value_list;
    GetMetadataCache(const_cast<string &>(args[1]), temp_value);
    RemoveMetadataCache(const_cast<string &>(args[1]));
    for(int i=0; i<temp_value.length(); i++){
        if(reinterpret_cast<const char *>(temp_value[i]) == " "){
            value_list.push_back(temp_value);
            push_value = "";
            continue;
        } else{
            push_value += temp_value[i];
        }
    }

    for (int i = 2; i < args.size(); i += 2) {
        if (args[i] == "parent") {
            value_list[0] = args[i + 1];
        }
        else if (args[i] == "modification_time") {
            value_list[2] = args[i + 1];
        }
        else if (args[i] == "name") {
            value_list[4] = args[i + 1];
        }
        else {
            feedback = "[ERROR] unknown key value.";
            return;
        }
    }

    temp_value.clear();
    for(auto i : value_list) {
        temp_value.append(i);
    }
    PutMetadataCache(const_cast<string &>(args[1]), temp_value);
    feedback = "Success";
}

MetadataSystem* MetadataSystem::GetClassType(void) {
    return this;
}

void MetadataSystem::InitKVengine() {
    LOG("Creating config");
    s = cfg.put_path(poolname+".poolset");
    ASSERT(s == pmem::kv::status::OK);
    s = cfg.put_size(SIZE);
    ASSERT(s == pmem::kv::status::OK);
    s = cfg.put_create_if_missing(true);
    ASSERT(s == pmem::kv::status::OK);

    LOG("Opening pmemkv database with 'cmap' engine");
    s = kv.open("cmap", std::move(cfg));
    ASSERT(s == pmem::kv::status::OK);

}

void MetadataSystem::PutMetadataCache(string& key, string& value) {
    LOG("Putting new key");
    s = kv.put(key, value);
    ASSERT(s == pmem::kv::status::OK);
}

void MetadataSystem::GetMetadataCache(string &key, string &value) {
    LOG("Reading key back");
    s = kv.get("key1", &value);
    ASSERT(s == pmem::kv::status::OK );
}

void MetadataSystem::RemoveMetadataCache(std::string &key) {
    LOG("Removing existing key");
    s = kv.remove(key);
    ASSERT(s == pmem::kv::status::OK);
}

void MetadataSystem::setPoolname(const string &poolname) {
    MetadataSystem::poolname = poolname;
}
