//
// Created by yyx on 2022/1/22.
//

#ifndef TINY_METADATA_SERVER_SYSTEM_CLASS_H
#define TINY_METADATA_SERVER_SYSTEM_CLASS_H


#include <string>
#include <vector>

class SystemClass {
public:
    virtual void ExecuteCommand(const std::vector<std::string>& command_args, std::string& feedback) = 0;
};

#endif //TINY_METADATA_SERVER_SYSTEM_CLASS_H
