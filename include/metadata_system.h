//
// Created by yyx on 2022/1/23.
//

#ifndef TINY_METADATA_SERVER_METADATA_SYSTEM_H
#define TINY_METADATA_SERVER_METADATA_SYSTEM_H

#include "system_class.h"
#include "file_system.h"
#include "metadata_node.h"
#include "socket.h"
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <map>
#include <libpmemkv.hpp>

class MetadataSystem : public SystemClass {
public:
    explicit MetadataSystem(MetadataServer* owner);
    ~MetadataSystem();
    void ExecuteCommand(const std::vector<std::string>& command_args, std::string& feedback) override;
    void InitKVengine(const std::string &poolpath);
    void PutMetadataCache(std::string& key, std::string& value);
    void GetMetadataCache(std::string& key, std::string& value);
    void RemoveMetadataCache(std::string& key);
    MetadataSystem* GetClassType(void);

private:
    MetadataServer* owner_;
    std::map<int, MetadataNode*> metadata_map_;
    pmem::kv::db kv;
    pmem::kv::config cfg;
    pmem::kv::status s;
    static void wup(const std::vector<std::string>& args, std::string& feedback);
    void request(const std::vector<std::string>& args, std::string& feedback);
    void remove(const std::vector<std::string>& args, std::string& feedback);
    void create(const std::vector<std::string>& args, std::string& feedback);
    void update(const std::vector<std::string>& args, std::string& feedback);
    void pushto(const std::vector<std::string>& args, std::string& feedback);

};

#endif //TINY_METADATA_SERVER_METADATA_SYSTEM_H
