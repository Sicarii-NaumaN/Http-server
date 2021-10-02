//
// Created by naum on 27.09.2021.
//

#include <iostream>

#include "utils/config_parser.hpp"
#include "server/server.hpp"

int main(int argc, char** argv) {
    auto path = std::string("../httpd.conf");
    if (argc > 1) {
        path = std::string(argv[1]);
    }

    auto config = config_parser(path);

    int port = 80;
    if (argc > 2) {
        port = std::stoi(argv[2]);
    }
    server ser = server();
    std::cout << ser.get_status(404) << std::endl << ser.get_method("HEAD");

    return 0;
}