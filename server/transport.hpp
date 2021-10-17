//
// Created by Yashuvaev Naum on 02.10.2021.
//

#ifndef SERVER_TRANSPORT_HPP
#define SERVER_TRANSPORT_HPP

#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <shared_mutex>
#include <thread>

#include "request.hpp"
#include "response.hpp"

class transport {
public:
    explicit transport(boost::asio::io_service &io_service, std::string  doc_root, const size_t& threads_count);
    boost::asio::ip::tcp::socket& get_socket();
    std::string& get_storage_path();
    void handle_request(int& threads_count);
    void add(int& threads_count);

private:
    void done(int& threads_count);
private:
    int max_threads = 0;
    request req;
    response resp;
    std::string docs_storage;
    boost::asio::ip::tcp::socket socket;

    std::shared_mutex limit_blocker;
    std::shared_mutex mutex_threads;
};


#endif //SERVER_TRANSPORT_HPP
