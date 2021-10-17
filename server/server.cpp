//
// Created by Yashuvaev Naum on 02.10.2021.
//

#include "server.hpp"
#include <thread>

void server::init_thread() {
    _socket_transport = std::make_shared<transport>(_io_service, _root, max_threads);
//    std::shared_ptr<boost::asio::ip::tcp::socket> socket = std::make_shared<boost::asio::ip::tcp::socket>(_io_service);
    _acceptor.async_accept(
            _socket_transport->get_socket(), [this](const boost::system::error_code &error) {
                if (error) {
                    std::cerr << "Can not accept connections: " << error.message() << std::endl;
                    return;
                }
                _socket_transport->add(std::ref(_threads_count));

                std::thread([](const std::shared_ptr<transport>& socket, int& threads_count) {
                                socket->handle_request(threads_count);
                            }, _socket_transport, std::ref(_threads_count)
                ).detach();
                init_thread();
            });

}

void server::run_server() {
    server::init_thread();
    _io_service.run();
}

server::server(const std::string &addr, const size_t &port, std::string &doc_root, const size_t& max_threads) :
        _io_service(),
        _root(doc_root),
        max_threads(max_threads),
        _acceptor(_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(addr), port)) {
}

