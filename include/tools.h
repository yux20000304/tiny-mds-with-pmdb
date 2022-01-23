//
// Created by yyx on 2022/1/23.
//

#ifndef TINY_METADATA_SERVER_TOOLS_H
#define TINY_METADATA_SERVER_TOOLS_H

#include <vector>
#include <string>

void ListIp();

// Split the input string at every delimiter, return a vector<string> containing the split results.
std::vector<std::string> SplitString(const std::string &in_string, const std::string &delimiters = std::string(" \t\r\n"));

void Error(const char* message);

#endif //TINY_METADATA_SERVER_TOOLS_H
