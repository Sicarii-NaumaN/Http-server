//
// Created by Yashuvaev Naum on 02.10.2021.
//

#include "request.hpp"

#include <sstream>

const std::string &request::get_method() {
    return method;
}

const std::string &request::get_path() {
    return path;
}

const std::string &request::get_protocol() {
    return protocol;
}

bool request::parse_request(const char *data) {
    std::istringstream iss(data);
    return iss >> method && iss >> path && iss >> protocol;
}
