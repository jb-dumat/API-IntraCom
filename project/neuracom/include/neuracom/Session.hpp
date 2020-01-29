#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>

#include "TcpSocket.hpp"
#include "Interpreter.hpp"

namespace net {
    class Session {
    public:
        explicit Session(std::shared_ptr<ISocket> &socket)
                : _socket(socket), _interpreter(SERVER_MAP)
        {
            _socket->setReceive([&](const char *data, size_t size) { readPayload(data, size); });
            _socket->setDisconnect([&](net::ISocket*) { this->stop(); });
        }

        void readPayload(const char *data, size_t size) {
                std::string msg(data, size);
                std::string response;

                // Log message
                std::cout << std::hex << "> Received msg: " << data << std::endl;

                auto args = net::Interpreter::parse(msg);
                response = _interpreter.interpret(args);

                // Any cleaner solution ?
                if (response == "DISCONNECT") {
                    this->shutdownStream();
                    return;
                }

                // Log response
                _socket->send(response);
        }

        void shutdownStream() {
            // Log something
            dynamic_cast<TCPSocket*>(_socket.get())->get().shutdown(boost::asio::socket_base::shutdown_both);
        }

        void stop() {
            std::cout << "[ Session " << _socket.get() << " has disconnected. ]" << std::endl;
        }

        static std::unordered_map<std::string, net::commandFunctor> SERVER_MAP;

    private:
        std::shared_ptr<ISocket> _socket;
        Interpreter _interpreter;
    };
}