//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_HTTP_HPP
#define SERVER_HTTP_HPP

#include <iostream>
#include <string>
#include <vector>

namespace header {
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
    constexpr content_type javascript = "application/javascript";
    constexpr content_type shockwave_flash = "application/x-shockwave-flash";

    // response status
    using status_code = std::string_view;
    constexpr status_code status_ok = "200 OK\r\n";
    constexpr status_code status_bad_request = "400 Bad Request\r\n";
    constexpr status_code status_forbidden = "403 Forbidden\r\n";
    constexpr status_code status_not_found = "404 Not Found\r\n";
    constexpr status_code status_not_allowed = "405 Method Not Allowed\r\n";
}

class http {
public:
    http() = default;
    ~http() = default;

    bool get_allowed_method(const std::string &method);
    std::string_view get_status(const size_t& code) const;
    std::string_view get_content(const std::string &type) const;
};


#endif //SERVER_HTTP_HPP
