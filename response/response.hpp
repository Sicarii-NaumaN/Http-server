//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_RESPONSE_HPP
#define SERVER_RESPONSE_HPP


#include "http.hpp"

#include <filesystem>
#include <fstream>
#include <cstring>

class response {
public:
    response() = default;
    std::string get_response(const std::string& method, std::string url, const std::string& version);

private:
    std::string get_status_code(const std::string& method, std::string& raw_url,
                                std::string& headers, int& resp_code);
    std::string get_date();
    std::string get_content_type(const std::string& type);

    std::string decode_url(const char *src);
private:
    http  http_header_methods;
};


#endif //SERVER_RESPONSE_HPP
