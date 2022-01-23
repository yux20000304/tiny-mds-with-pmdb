//
// Created by yyx on 2022/1/22.
//

#ifndef TINY_METADATA_SERVER_METADATA_SERVER_H
#define TINY_METADATA_SERVER_METADATA_SERVER_H

#include "system_class.h"
#include "file_system.h"
#include "socket.h"
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <map>


class MetadataServer {
public:
    MetadataServer(std::string self_ip, int self_port, std::string master_ip, int master_port, int slave_num);
    void WhichSlaveToStore(int file_id, std::vector<int>& slaves) const;
    void CheckSlaveStats(std::string& result);
    static void SendMessageToSlaveIp(const std::string& slave_ip, int slave_port, const std::string& message, std::string& result);
    void SendMessageToSlaves(const std::vector<int>& slaves, const std::string& message, std::string& result);
    void Run();

private:
    ServerSocket* server_socket_;
    bool is_master_;
    std::string self_ip_;
    const int self_port_;
    const std::string master_ip_;
    const int master_port_;
    int self_slave_id_;
    const int slave_num_;
    std::vector<std::vector<std::string> > slave_table_;
    std::vector<ClientSocket*> client_sockets_;
    std::vector<bool> connection_stats_;
    std::vector<bool> need_replacement_stats_;

    void InitMaster();
    void InitSlave();
    std::string GetSlaveInfoFromId(int slave_id);
    void ConnectSlave(int slave_id);
    bool SyncSlaves(int src_slave_id, int dst_slave_id);
    bool RecoverSlave(int slave_id);

    [[noreturn]] void Run(SystemClass* inner_system);
};


class MetadataNode {
public:
    MetadataNode(int id, int parent, std::string creation_time, size_t size,
                 std::string modification_time, std::string name, int type):
            id_(id), parent_(parent), creation_time_(std::move(creation_time)),
            modification_time_(std::move(modification_time)), size_(size), name_(std::move(name)),
            type_(type){}

    void set_parent(int parent) {
        parent_ = parent;
    }

    void set_modification_time(const std::string &modification_time) {
        modification_time_ = modification_time;
    }

    void set_name(const std::string &name) {
        name_ = name;
    }

    std::string GetSummary() {
        std::stringstream summary;
        summary << std::to_string(id_) << " " << std::to_string(parent_) << " "
                << creation_time_ << " " << modification_time_
                << " " << std::to_string(size_) << " " + name_ << " " << std::to_string(type_);
        return summary.str();
    }

    std::string GetInfo() {
        std::stringstream info;
        info << "OID: " << id_ << " PID: " << parent_ << " Size: " << size_ << " Name: " << name_ << " IsFile: " << type_
             << "\nCreationTime: " << creation_time_
             << "\nModification: " << modification_time_
             << "\n--------------------------------------";
        return info.str();
    }

private:
    const int id_;
    int parent_;
    const std::string creation_time_;
    std::string modification_time_;
    size_t size_;
    std::string name_;
    const int type_;
};


class MetadataSystem : public SystemClass {
public:
    explicit MetadataSystem(MetadataServer* owner);
    ~MetadataSystem();
    void ExecuteCommand(const std::vector<std::string>& command_args, std::string& feedback) override;

private:
    MetadataServer* owner_;
    std::map<int, MetadataNode*> metadata_map_;
    static void wup(const std::vector<std::string>& args, std::string& feedback);
    void request(const std::vector<std::string>& args, std::string& feedback);
    void remove(const std::vector<std::string>& args, std::string& feedback);
    void create(const std::vector<std::string>& args, std::string& feedback);
    void update(const std::vector<std::string>& args, std::string& feedback);
    void pushto(const std::vector<std::string>& args, std::string& feedback);
};



#endif //TINY_METADATA_SERVER_METADATA_SERVER_H
