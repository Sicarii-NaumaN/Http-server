//
// Created by Yashuvaev Naum on 02.10.2021.
//

#include "response.hpp"

#define BUF_SIZE 1024

std::string response::get_response(const std::string& method, std::string url, const std::string& version) {
    std::stringstream resp_ss;
    resp_ss << version << ' ';
    std::stringstream headers_ss;
    headers_ss << "Server: server\r\n"
               << "Date: " << get_date() << "\r\n"
               << "Connection: Closed\r\n";
    std::string headers = headers_ss.str();
    int resp_code;
    resp_ss << get_status_code(method, url, headers, resp_code) << headers << "\r\n";
    std::string response =  resp_ss.str();
    if (method == header::method_head) {
        return response;
    }
    if (resp_code == 200) {
        std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
        char buf[BUF_SIZE];
        while (file.read(buf, sizeof(buf)).gcount() > 0) {
            response.append(buf, file.gcount());
        }
    }
    return response;
}

std::string response::decode_url(const char *src) {
    std::string uri;
    while (*src) {
        if (*src == '%' && isxdigit(*(src + 1)) && isxdigit(*(src + 2))) {
            char buf[3];
            memcpy(buf, src + 1, 2);
            std::stringstream ss;
            ss << std::hex << buf;
            int character;
            ss >> character;
            uri.push_back(static_cast<char>(character));
            src += 3;
        } else if (*src == '+') {
            uri.push_back(' ');
            src++;
        } else {
            uri.push_back(*src++);
        }
    }
    return uri;
}


std::string response::get_status_code(const std::string& method, std::string& raw_url,
                                      std::string& headers, int& resp_code) {
    if (!http_header_methods.get_allowed_method(method)) {
        return std::string(http_header_methods.get_status(405));
    }

    size_t q_params = raw_url.find('?');
    if (q_params != std::string::npos) {
        raw_url = raw_url.substr(0, q_params);
    }

    raw_url = decode_url(raw_url.data());
    size_t last_slash_index = raw_url.find_last_of('/');

    if (raw_url.find("../") != std::string::npos) {
        return std::string(http_header_methods.get_status(403));;
    }

    if (!std::filesystem::exists(raw_url)) {
        return std::string(http_header_methods.get_status(404));
    }

    if (last_slash_index == raw_url.length() - 1) {
        raw_url += "index.html";
    }

    if (!std::filesystem::exists(raw_url)) {
        return std::string(http_header_methods.get_status(403));;
    }

    size_t ext_index = raw_url.find_last_of('.');
    std::string content_type = get_content_type(raw_url.substr(ext_index + 1, raw_url.length() - ext_index));
    std::stringstream hstream;
    hstream << "Content-Type: " << content_type << "\r\n"
            << "Content-Length: " << std::filesystem::file_size(raw_url) << "\r\n";
    headers.append(hstream.str());
    resp_code = 200;
    return std::string(http_header_methods.get_status(200));
}

std::string response::get_content_type(const std::string& type) {
    return  std::string(http_header_methods.get_content(type));
}

std::string response::get_date() {
    std::time_t timer = std::time(nullptr);
    char buf[BUF_SIZE];
    auto timeNow = std::strftime(buf, sizeof(buf),
                                 "%a, %d %b %Y %H:%M:%S GMT",
                                 std::localtime(&timer));
    return std::string(buf, timeNow);
}
