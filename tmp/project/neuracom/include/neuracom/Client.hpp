//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "NetworkService.hpp"
#include "TcpSocket.hpp"
#include "Interpreter.hpp"

#include <thread>

namespace net {
    class Client {
    public:
        Client(NetworkService &ioContext, const std::string &ip, int port)
                : _ioContext(ioContext), _socket(_ioContext), _inter(CLIENT_MAP) {
            _socket.connect(port, ip);
            _socket.setReceive([&](const char *data, size_t size) { handleReceive(data, size); });
        }

        void handleReceive(const char *data, size_t size) {
            std::string msg(data, size);
            std::string response;

            std::cout << "> Received msg: " << data << std::endl;

            // Interpret the response
            auto args = net::Interpreter::parse(msg);
            response = _inter.interpret(args);
        }

        static std::unordered_map<std::string, commandFunctor> CLIENT_MAP;

    private:
        NetworkService &_ioContext;
        TCPSocket _socket;
        Interpreter _inter;
    };

    std::unordered_map<std::string, net::commandFunctor> net::Client::CLIENT_MAP;
}