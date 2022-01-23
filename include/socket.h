//
// Created by yyx on 2022/1/22.
//

#ifndef TINY_METADATA_SERVER_SOCKET_H
#define TINY_METADATA_SERVER_SOCKET_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

#define BufferSize 1024

//definition of client socket
class ClientSocket {
public:
    ClientSocket(const std::string& hostname, int port);
    bool GetMessage(std::string& message) const;
    bool SendMessage(const std::string& message) const;
    int get_sock_ret() const;
    ~ClientSocket();
private:
    int sock_ret;
    int client_port;
    struct sockaddr_in server_addr;
    struct hostent *server_info;
};



//definition of server socket
class ServerSocket {
public:
    ServerSocket(int port);
    int connection();
    std::string GetClientAddr();
    bool GetMessage(std::string& message);
    bool SendMessage(const std::string& message);
    ~ServerSocket();

private:
    int sock_ret;
    int client_sock_ret;
    int server_port;
    sockaddr_in server_addr, client_addr;
    sockaddr *p_client_addr;
    socklen_t client_addr_length;
    std::string client_addr_string;
};


#endif //TINY_METADATA_SERVER_SOCKET_H
