//
// Created by Yashuvaev Naum on 02.10.2021.
//

#include "server.hpp"

std::string_view server::get_method(const std::string &method) const {
    if (method == http::method_head) {
        return http::method_head;
    } else if (method == http::method_get) {
        return http::method_get;
    }
    return std::string_view("");
}

std::string_view server::get_status(const size_t& code) const {
    switch (code) {
        case 200:
            return http::status_ok;
        case 400:
            return http::status_bad_request;
        case 403:
            return http::status_forbidden;
        case 404:
            return http::status_not_found;
        case 405:
            return http::status_not_allowed;
        default:
            return std::string_view("");
    }
    return std::string_view("");
}

std::string_view server::get_content(const std::string &type) const {
    if (type == http::plain) {
        return http::plain;
    } else if (type == http::css) {
        return http::css;
    } else if (type == http::html) {
        return http::html;
    } else if (type == http::jpg) {
        return http::jpg;
    } else if (type == http::png) {
        return http::png;
    } else if (type == http::tif) {
        return http::tif;
    }

    return std::string_view("");
}