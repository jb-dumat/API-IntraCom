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
#include <utility>

namespace net {
    class Client {
    public:
        explicit Client(NetworkService &ioContext, const std::string &ip, int port)
            : _ioContext(ioContext), _socket(_ioContext), _inter(CLIENT_MAP), _eventCb(nullptr)
        {
            _socket.connect(port, ip);
            _socket.setReceive([&](const char *data, size_t size) { handleReceive(data, size); });
        }

        explicit Client(NetworkService &ioContext, const std::string &ip, int port, std::function<void(const std::string&)> eventCb)
            : _ioContext(ioContext), _socket(_ioContext), _inter(CLIENT_MAP), _eventCb(std::move(eventCb))
        {
            _socket.connect(port, ip);
            _socket.setReceive([&](const char *data, size_t size) { handleReceive(data, size); });
        }

        void handleReceive(const char *data, size_t size) {
            std::string msg(data, size);

            if (_eventCb)
                _eventCb("Received msg: " + msg);

            // Interpret the response
            auto&& args = net::Interpreter::parse(std::move(msg));
            auto&& response = _inter.interpret(std::move(args));

            if (_eventCb)
                _eventCb("Send msg: " + response);
        }

        void manualSend(const std::string& msg)
        {
            _socket.send(msg);
        }

        static std::unordered_map<std::string, commandFunctor> CLIENT_MAP;

    private:
        NetworkService &_ioContext;
        TCPSocket _socket;
        Interpreter _inter;
        std::function<void(const std::string&)>  _eventCb;
    };
}