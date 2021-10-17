//
// Created by naum on 27.09.2021.
//

#include <iostream>

#include "utils/config_parser.hpp"
#include "server/server.hpp"


#define MAX_EVENTS 5
#define READ_SIZE 10

int main(int argc, char** argv) {
    std::string path = std::string("../httpd.conf");
    if (argc > 1) {
        path = std::string(argv[1]);
    }

    auto config = config_parser(path);

    size_t port = 8080;
    std::string host = "127.0.0.1";
    if (argc > 2) {
        port = std::stoi(argv[2]);
    }
    std::cout << "starting\n";
    server ser = server(host, port, config.document_root, config.threads_limit);
    ser.run_server();
//    auto request = request


    return 0;
}
