//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_REQUEST_HPP
#define SERVER_REQUEST_HPP

#include <string>

class request {
public:
    explicit request() = default;
    bool parse_request(const char* data);

    const std::string& get_method();
    const std::string& get_path();
    const std::string& get_protocol();
private:
    std::string method;
    std::string path;
    std::string protocol;
};



#endif //SERVER_REQUEST_HPP

// curl -4 icanhazip.com