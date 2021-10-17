//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include "http.hpp"
#include "request.hpp"
#include "transport.hpp"
#include "response.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/error_code.hpp>



class server {
public:
    server() = delete;
    explicit server(const std::string& addr, const size_t& port, std::string& doc_root,const size_t& max_threads);

    void run_server();
private:
    std::string _root;
    std::shared_ptr<transport> _socket_transport;
//    std::vector<std::thread> _workers{};
    int _threads_count = 0;
    const size_t max_threads;
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::acceptor _acceptor;

private:
    void init_thread();
};

#endif //SERVER_SERVER_HPP
