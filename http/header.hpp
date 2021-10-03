//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_HEADER_HPP
#define SERVER_HEADER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace http {
    // Http type
    using method = std::string_view;
    constexpr method method_get = "GET";
    constexpr method method_head = "HEAD";

    // Content-type
    using content_type = std::string_view;
    constexpr content_type plain = "text/plain";
    constexpr content_type css = "text/css";
    constexpr content_type html = "text/html";
    constexpr content_type png = "image/png";
    constexpr content_type jpg = "image/jpeg";
    constexpr content_type tif = "image/tiff";
    constexpr content_type gif = "image/gif";
    constexpr content_type bpm = "image/bmp";
    constexpr content_type javascript = "application/javascript";
    constexpr content_type shockwave_flash = "application/x-shockwave-flash";

    // Response status
    using status_code = std::string_view;
    constexpr status_code status_ok = "200 OK";
    constexpr status_code status_bad_request = "400 Bad Request";
    constexpr status_code status_forbidden = "403 Forbidden";
    constexpr status_code status_not_found = "404 Not Found";
    constexpr status_code status_not_allowed = "405 Method Not Allowed";
}

class header {
public:
    header() = default;
    ~header() = default;

    std::string_view get_method(const std::string& method) const;
    std::string_view get_status(const size_t& code) const;
    std::string_view get_content(const std::string &type) const;
};


#endif //SERVER_HEADER_HPP
