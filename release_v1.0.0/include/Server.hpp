#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include "TcpSocket.hpp"
#include "Interpreter.hpp"

namespace net {

    class Server {
    public:
        explicit Server(std::shared_ptr<ISocket> &socket)
                : _socket(socket), _interpreter(SERVER_MAP) {
            _socket->setReceive([&](const char *data, size_t size) { handleReceive(data, size); });
        }

        void handleReceive(const char *data, size_t size) {
            std::string msg(data, size);
            std::string response;

            std::cout << "> Received msg: " << data << std::endl;

            auto args = net::Interpreter::parse(msg);
            response = _interpreter.interpret(args);
            // Log response
        }

        static std::unordered_map<std::string, commandFunctor> SERVER_MAP;

    private:
        std::shared_ptr<ISocket> _socket;
        Interpreter _interpreter;
    };

    std::unordered_map<std::string, net::commandFunctor> net::Server::SERVER_MAP;

}