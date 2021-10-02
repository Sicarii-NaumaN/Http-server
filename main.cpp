//
// Created by naum on 27.09.2021.
//

#include <iostream>

#include "utils/ConfigParser.hpp"

int main(int argc, char** argv)
{
    auto path = std::string("../httpd.conf");
    if (argc > 1) {
        path = std::string(argv[1]);
    }

    ConfigParser config;
    try {
        config = ConfigParser(path);
    }
    catch (...) {
        std::cerr << "Config error";
    }

    int port = 8080;
    if (argc > 2) {
        port = std::stoi(argv[2]);
    }

    return 0;
}