//
// Created by yyx on 2022/1/22.
//

#include "socket.h"
#include "tools.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <fstream>


#define BufferSize 1024


using namespace std;


void PrintHelp() {
    std::cout <<
              "--master_ip_/-i  <string>:      Set IP of the master server.\n"
              "--masterPort/-p   <int>:      Set port of the master server.\n"
              "--file_input/-f   <string>    Set input file path.\n"
              "--help/-h              :      Show help.\n";
    exit(1);
}




int main(int argc, char *argv[])
{
    string master_address;
    int master_port = 0;
    string input_file_path;

    bool opt_flags[] = {0, 0, 0, 0};
    const char* const short_opts = "i:p:f:h";
    const option long_opts[] = {
            {"masterIp", required_argument, nullptr, 'i'},
            {"masterPort", required_argument, nullptr, 'p'},
            {"input_file", required_argument, nullptr, 'f'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (-1 == opt)
            break;
        switch (opt) {

            case 'i':
                master_address = string(optarg);
                std::cout << "Master IP is set to: " << master_address << endl;
                opt_flags[0] = true;
                break;

            case 'p':
                master_port = stoi(optarg);
                std::cout << "Master port is set to: " << master_port << endl;
                opt_flags[1] = true;
                break;

            case 'f':
                input_file_path = string(optarg);
                std::cout << "input stream is set to file: " << input_file_path << endl;
                opt_flags[2] = true;
                break;

            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                PrintHelp();
                break;
        }
    }
    if (!(opt_flags[0] && opt_flags[1]))
        PrintHelp();

    ClientSocket connection_socket(master_address, master_port);

    char buffer[BufferSize];
    ifstream in(input_file_path);
    string in_string;

    //read from file
    if (opt_flags[2]){

        struct timeval start, stop, diff;
        memset(&start, 0, sizeof(struct timeval));
        memset(&stop, 0, sizeof(struct timeval));
        memset(&diff, 0, sizeof(struct timeval));
        gettimeofday(&start, 0);

        while (true) {
            if (!getline(in, in_string)) {
//                gettimeofday(&stop, 0);
//                time_substract(&diff, &start, &stop);
//                printf("throughput time : %d s,%d us\n", (int) diff.tv_sec, (int) diff.tv_usec);
                break;
            }
            vector <string> commands;
            commands = SplitString(in_string);
            if (commands.empty()){
                continue;
            }
            else {
                if (commands[0] == "exit" or commands[0] == "quit" or commands[0] == "q")
                    break;
                else {
                    string message(in_string);
                    if (!connection_socket.SendMessage(message)) {
                        connection_socket = ClientSocket(master_address, master_port);
                        continue;
                    }
                    string tmp_message;
                    if (!connection_socket.GetMessage(tmp_message)) {
                        connection_socket = ClientSocket(master_address, master_port);
                        continue;
                    }

                    if (tmp_message != "[EMPTY]") {
                        cout << tmp_message;
                    }
                }
            }
        }
        gettimeofday(&stop, 0);
        time_substract(&diff, &start, &stop);
        printf("latency time : %d s,%d us\n", (int) diff.tv_sec, (int) diff.tv_usec);

    }
    //read from commandline
//    else{
        while (true) {
            cout << "> ";
            bzero(buffer, BufferSize);
            fgets(buffer, BufferSize - 1, stdin);
            in_string = string(buffer);

            vector <string> commands;
            commands = SplitString(in_string);
            if (commands.empty())
                continue;
            else {
                if (commands[0] == "exit" or commands[0] == "quit" or commands[0] == "q")
                    break;
                else {
                    string message(in_string);
                    struct timeval start, stop, diff;
                    memset(&start, 0, sizeof(struct timeval));
                    memset(&stop, 0, sizeof(struct timeval));
                    memset(&diff, 0, sizeof(struct timeval));
                    gettimeofday(&start, 0);
                    if (!connection_socket.SendMessage(message)) {
                        connection_socket = ClientSocket(master_address, master_port);
                        continue;
                    }
                    string tmp_message;
                    if (!connection_socket.GetMessage(tmp_message)) {
                        connection_socket = ClientSocket(master_address, master_port);
                        continue;
                    }
                    if (tmp_message != "[EMPTY]") {
                        cout << tmp_message;
                    }
                    gettimeofday(&stop, 0);
                    time_substract(&diff, &start, &stop);
                    printf("command time : %d s,%d us\n", (int) diff.tv_sec, (int) diff.tv_usec);
                }
            }
        }
//    }
    return 0;
}