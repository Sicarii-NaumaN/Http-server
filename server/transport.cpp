//
// Created by Yashuvaev Naum on 02.10.2021.
//

#include "transport.hpp"

#include <iostream>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/completion_condition.hpp>
#include <utility>
#include <boost/asio/write.hpp>


transport::transport(boost::asio::io_service &io_service, std::string  doc_root, const size_t& max_threads)
                    : docs_storage(std::move(doc_root)), socket(io_service), max_threads(max_threads), req(), resp() {

}

boost::asio::ip::tcp::socket& transport::get_socket() {
    return socket;
}

std::string &transport::get_storage_path() {
    return docs_storage;
}

void transport::done(int& threads_count) {
    mutex_threads.lock();

    threads_count--;
    std::cout << std::this_thread::get_id() <<" Decrementing thread " << threads_count << std::endl;
    if (threads_count < max_threads)
        limit_blocker.unlock();

    mutex_threads.unlock();

}

void transport::add(int& threads_count) {
    mutex_threads.lock();
    threads_count++;
    std::cout << std::this_thread::get_id() <<" Incrementing thread " << threads_count << std::endl;
    if (threads_count <= max_threads) {
        limit_blocker.unlock();
    }

    mutex_threads.unlock();
}

void transport::handle_request(int& threads_count) {
    try {
        boost::asio::streambuf buf;

        boost::asio::read_until(socket, buf, "\r\n");
        std::string r_data((std::istreambuf_iterator<char>(&buf)),
                           std::istreambuf_iterator<char>());
        if (!req.parse_request(r_data.c_str())) {
            std::cerr << "Error during parsing request " << r_data << std::endl;
        } else {
            std::string response = resp.get_response(req.get_method(), docs_storage + req.get_path(), req.get_protocol());
            boost::asio::write(socket, boost::asio::buffer(response), boost::asio::transfer_all());
        }
        socket.close();

        done(std::ref(threads_count));
    } catch (std::exception &e) {
        std::cerr << "Error during handle: " << e.what() << std::endl;
    }
}

