//
// Created by naum on 27.09.2021.
//

#ifndef HTTP_SERVER_CONFIG_PARSER_H
#define HTTP_SERVER_CONFIG_PARSER_H


#include <string>

class ConfigParser {
public:
    explicit ConfigParser(std::string path);

    ConfigParser() = default;

    ~ConfigParser() = default;

    size_t GetThreadsLimit();

    size_t GetMaxConn();

    std::string GetDocRoot();

private:
    std::size_t threads_limit{};
    std::size_t max_connections{};
    std::string document_root;
};

#endif //HTTP_SERVER_CONFIG_PARSER_H
