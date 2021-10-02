//
// Created by naum on 27.09.2021.
//

#include <iostream>
#include <fstream>

#include "config_parser.hpp"


config_parser::config_parser(std::string& path) {
    std::ifstream conf_file(path, std::ifstream::in);
    std::string line;
    int pos;

    if (conf_file) {
        std::getline(conf_file, line);
        pos = line.find(' ');

        std::string value = line.substr(pos + 1, line.length());
        try {
            threads_limit = std::stoi(value);
        }
        catch (...) {
            std::cerr << "Error while getting threads limit\n";
        }

        std::getline(conf_file, line);
        pos = line.find(' ');
        std::string mConn = line.substr(pos + 1, line.length());
        try {
            max_connections = std::stoi(mConn);
        }
        catch (...) {
            std::cerr << "Error while getting max connections\n";
        }


        std::getline(conf_file, line);
        pos = line.find(' ');
        document_root = line.substr(pos + 1, line.length());
    } else {
        std::cerr << "Error while parsing\n";
    }
}

size_t const config_parser::GetThreadsLimit() const {
    return threads_limit;
}

size_t const config_parser::GetMaxConn() const {
    return max_connections;
}

std::string const config_parser::GetDocRoot() {
    return document_root;
}
