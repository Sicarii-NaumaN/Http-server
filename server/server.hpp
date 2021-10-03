//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include "../http/header.hpp"


class server {
public:
    server() = default;
    ~server() = default;

    void run();
    void accept_clients();

    header header{};
    std::vector<std::thread> threads;
};


#endif //SERVER_SERVER_HPP
