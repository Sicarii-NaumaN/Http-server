//
// Created by Yashuvaev Naum on 02.10.2021.
//

#include "http.hpp"

bool http::get_allowed_method(const std::string &method) {
    return (method == header::method_head) || (method == header::method_get);
}

std::string_view http::get_status(const size_t &code) const {
    switch (code) {
        case 200:
            return header::status_ok;
        case 400:
            return header::status_bad_request;
        case 403:
            return header::status_forbidden;
        case 404:
            return header::status_not_found;
        case 405:
            return header::status_not_allowed;
        default:
            return std::string_view("");
    }
    return std::string_view("");
}

std::string_view http::get_content(const std::string &type) const {
    if (type == header::plain) {
        return header::plain;
    } else if (type == "css") {
        return header::css;
    } else if (type == "html") {
        return header::html;
    } else if (type == "png") {
        return header::png;
    } else if (type == "tif") {
        return header::tif;
    } else if (type == "swf") {
        return header::shockwave_flash;
    } else if (type == "js") {
        return header::javascript;
    } else if (type == "jpeg") {
        return header::jpg;
    } else if (type == "jpg") {
        return header::jpg;
    } else if (type == "gif") {
        return header::gif;
    }

    return std::string_view("");
}
