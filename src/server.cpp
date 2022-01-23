//
// Created by yyx on 2022/1/22.
//

#include "metadata_server.h"
#include "tools.h"
#include <string>
#include <iostream>
#include <getopt.h>


using namespace std;


void PrintHelp() {
    std::cout <<
              "--selfPort/-s     <int>:      Set local port to be used.\n"
              "--master_ip_/-i  <string>:      Set IP of the master server.\n"
              "--masterPort/-p   <int>:      Set port of the master server.\n"
              "--slaveNum/-n     <int>:      Set number of slave servers.\n"
              "--help/-h              :      Show help.\n\n";
    cout << "The detected IP addresses of this host is:" << endl;
    ListIp();
    exit(1);
}


int main(int argc, char *argv[]) {
    string self_address;
    int self_port = 0;
    string master_address;
    int master_port = 0;
    int slave_num = -1;

    bool opt_flags[] = {false, false, false, false};
    const char* const short_opts = "s:i:p:n:h";
    const option long_opts[] = {
            {"selfPort", required_argument, nullptr, 's'},
            {"masterIp", required_argument, nullptr, 'i'},
            {"masterPort", required_argument, nullptr, 'p'},
            {"slaveNum", required_argument, nullptr, 'n'},
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
                master_address = string(optarg);
                std::cout << "Master IP is set to: " << master_address << endl;
                opt_flags[1] = true;
                break;

            case 'p':
                master_port = stoi(optarg);
                std::cout << "Master port is set to: " << master_port << endl;
                opt_flags[2] = true;
                break;

            case 'n':
                slave_num = stoi(optarg);
                std::cout << "Slave number is set to: " << slave_num << std::endl;
                opt_flags[3] = true;
                break;

            case 'h': // -h or --help
            case '?': // Unrecognized option
            default:
                PrintHelp();
                break;
        }
    }
    if (!((opt_flags[0] && opt_flags[3]) || (opt_flags[0] && opt_flags[1] && opt_flags[2])))
        PrintHelp();

    if (opt_flags[0] && opt_flags[3])
        master_port = self_port;

    MetadataServer server(self_address, self_port, master_address, master_port, slave_num);
    server.Run();

    return 0;
}
