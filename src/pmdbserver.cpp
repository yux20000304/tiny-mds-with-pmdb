//
// Created by yyx on 2022/4/9.
//

#include "metadata_server.h"
#include "tools.h"
#include <string>
#include <iostream>
#include <getopt.h>
#include <sys/socket.h>


using namespace std;


void PrintHelp() {
    std::cout <<
              "--selfPort/-s     <int>:      Set local port to be used.\n"
              "--help/-h              :      Show help.\n\n";
    cout << "The detected IP addresses of this host is:" << endl;
    ListIp();
    exit(1);
}


int main(int argc, char *argv[]) {
    string self_address;
    int self_port = 0;
    string client_address;
    int client_port = 0;
    int slave_num = -1;

    bool opt_flags[] = {false, false, false, false};
    const char* const short_opts = "s:i:p:h";
    const option long_opts[] = {
            {"selfPort", required_argument, nullptr, 's'},
            {"clientIp", required_argument, nullptr, 'i'},
            {"clientPort", required_argument, nullptr, 'p'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (-1 == opt)
            break;
        switch (opt) {
            case 's':
                self_port = stoi(optarg);
                std::cout << "Self port is set to: " << self_port << endl;
                opt_flags[0] = true;
                break;

            case 'i':
                client_address = string(optarg);
                std::cout << "client IP is set to: " << client_address << endl;
                opt_flags[1] = true;
                break;

            case 'p':
                client_port = stoi(optarg);
                std::cout << "client port is set to: " << client_port << endl;
                opt_flags[2] = true;
                break;

            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                PrintHelp();
                break;
        }
    }
    if (!((opt_flags[0] ) || (opt_flags[0] && opt_flags[1] && opt_flags[2])))
        PrintHelp();


    ServerSocket *server_socket = new ServerSocket(self_port);

    while (true) {
        string received_message;
        vector<string> argv;
        string message;
        if (!server_socket->GetMessage(received_message)) {
            continue;
        }
        std::cout << received_message << endl;
        argv = SplitString(received_message);

        if (message.empty()) {
            message = "[EMPTY]";
        }
        else{
            string command = argv[0];
            if (command == "pwd") {

            }
            else if (command == "mkdir") {

            }
            else if (command == "ls") {

            }
            else if (command == "readdir") {

            }
            else if (command == "cd") {

            }
            else if (command == "mv") {

            }
            else if (command == "stat") {

            }
            else if (command == "touch") {

            }
            else if (command == "rm") {

            }
            else if (command == "serverstats") {

            }

        }
        if (!server_socket->SendMessage(message)) {
            continue;
        }
        cout << "↑\n";
        printf("%s",message.c_str());
        cout << endl;
    }


    return 0;
}



