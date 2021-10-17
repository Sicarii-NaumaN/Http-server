//
// Created by naum on 27.09.2021.
//

#ifndef HTTP_SERVER_CONFIG_PARSER_H
#define HTTP_SERVER_CONFIG_PARSER_H


#include <string>

class config_parser {
public:
    explicit config_parser(std::string& path);

    config_parser() = default;

    ~config_parser() = default;

    size_t GetThreadsLimit() const;

    size_t GetMaxConn() const;

    std::string GetDocRoot();

    std::size_t threads_limit{};
    std::size_t max_connections{};
    std::string document_root;
};

#endif //HTTP_SERVER_CONFIG_PARSER_H
