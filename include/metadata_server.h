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






#endif //TINY_METADATA_SERVER_METADATA_SERVER_H
