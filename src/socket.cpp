//
// Created by yyx on 2022/1/22.
//

#include "tools.h"
#include "socket.h"
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>
#include <iostream>

int fd_is_valid(int fd) {
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

void *GetAddress(struct sockaddr *socket_address) {
    if (socket_address->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)socket_address)->sin_addr);
    }
    return &(((struct sockaddr_in6*)socket_address)->sin6_addr);
}

std::string GetIpString(int ai_family, struct sockaddr *socket_address) {
    char ip_string[INET6_ADDRSTRLEN];
    inet_ntop(ai_family, GetAddress(socket_address), ip_string, sizeof ip_string);
    return std::string(ip_string);
}

ServerSocket::ServerSocket(int port) {
    signal(SIGPIPE, SIG_IGN);
    client_sock_ret = -1;
    bool flag = false;
    for (int i = 0; i < 8; ++i) {
        sock_ret = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_ret < 0)
            continue;

        bzero((char *) &(server_addr), sizeof(server_addr));
        server_port = port;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);
        if (bind(sock_ret, (struct sockaddr *) &(server_addr), sizeof(server_addr)) < 0)
            continue;
        listen(sock_ret, 16);
        client_addr_length = sizeof(client_addr);
        p_client_addr = (struct sockaddr *) &(client_addr);
        flag = true;
        break;
    }
    if (!flag) {
        std::cout << "[ERROR] Cannot open socket on port " << port << "!" << std::endl;
    }
    else {
        std::cout << "[Socket] Listening on port " << port << "..." << std::endl;
    }
}

int ServerSocket::connection() {
    client_sock_ret = accept(sock_ret, p_client_addr, &(client_addr_length));
    client_addr_string = GetIpString(AF_INET, p_client_addr);
    if (client_sock_ret < 0) {
        Error("[Socket] Accept connection failed!");
    }
    return client_sock_ret;
}

std::string ServerSocket::GetClientAddr(){
    return client_addr_string;
}

bool ServerSocket::GetMessage(std::string& message) {
    char buffer[BufferSize];
    bzero(buffer,BufferSize);
    int n = read(client_sock_ret, buffer, BufferSize - 1);
    if (n <= 0) {
        std::cout << "[WARNING] Socket disconnected!" << std::endl;
        connection();
        return false;
    }
    message = std::string(buffer);
    return true;
}

bool ServerSocket::SendMessage(const std::string& message) {
    if (!fd_is_valid(sock_ret)) {
        std::cout << "[ERROR] Invalid socket file descriptor!" << std::endl;
        return false;
    }
    int n = write(client_sock_ret, message.c_str(), message.size());
    if (n <= 0) {
        std::cout << "[WARNING] Socket disconnected!" << std::endl;
        connection();
        return false;
    }
    return true;
}

ServerSocket::~ServerSocket() {
    close(client_sock_ret);
    close(sock_ret);
}

ClientSocket::ClientSocket(const std::string& hostname, int port) {
    signal(SIGPIPE, SIG_IGN);
    client_port = port;
    server_info = gethostbyname(hostname.c_str());
    if (server_info == nullptr) {
        std::cout << "[ERROR] Failed to get server info!" << std::endl;
        return;
    }
    sock_ret = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ret < 0) {
        std::cout << "[ERROR] Failed to open socket!" << std::endl;
        return;
    }
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server_info->h_addr,
          (char *)&server_addr.sin_addr.s_addr,
          server_info->h_length);
    server_addr.sin_port = htons(client_port);
    if (connect(sock_ret, (struct sockaddr *) &(server_addr), sizeof(server_addr)) < 0) {
        std::cout << "[WARNING] Socket disconnected!" << std::endl;
        return;
    }
}

int ClientSocket::get_sock_ret()  const {
    return sock_ret;
}

bool ClientSocket::GetMessage(std::string& message) const {
    char buffer[BufferSize];
    bzero(buffer,BufferSize);
    int n = read(sock_ret, buffer, BufferSize - 1);
    if (n < 0) {
        std::cout << "[WARNING] Socket disconnected!" << std::endl;
        return false;
    }
    message = std::string(buffer);
    return true;
}

bool ClientSocket::SendMessage(const std::string& message) const {
    if (!fd_is_valid(sock_ret)) {
        std::cout << "[ERROR] Invalid socket file descriptor!" << std::endl;
        return false;
    }
    int n = write(sock_ret, message.c_str(), message.size());
    if (n < 0) {
        std::cout << "[WARNING] Socket disconnected!" << std::endl;
        return false;
    }
    return true;
}

ClientSocket::~ClientSocket() {
    close(sock_ret);
}