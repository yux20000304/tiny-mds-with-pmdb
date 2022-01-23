//
// Created by yyx on 2022/1/23.
//

#ifndef TINY_METADATA_SERVER_METADATA_NODE_H
#define TINY_METADATA_SERVER_METADATA_NODE_H

#include "system_class.h"
#include "file_system.h"
#include "socket.h"
#include <string>
#include <vector>
#include <map>

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


#endif //TINY_METADATA_SERVER_METADATA_NODE_H
