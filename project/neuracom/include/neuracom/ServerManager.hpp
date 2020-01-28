#pragma once

#include <memory>
#include <vector>

#include "NetworkService.hpp"
#include "TcpAcceptor.hpp"
#include "ISocket.hpp"
#include "Server.hpp"

namespace net {
    class ServerManager {
    public:
        ServerManager(NetworkService &ioContext, uint16_t port)
                : _ioContext(ioContext), _acceptor(_ioContext), _port(port) {}

        void launch() {
            _acceptor.bind(_port);
            _acceptor.accept<TCPSocket>([&](const std::shared_ptr<ISocket>& socket) {
                std::cout << "Accepted new connection " << socket.get() << std::endl;
                acceptSession(socket);
            });
        }

        void acceptSession(std::shared_ptr<ISocket> socket) {
            _sessions.emplace_back(new Server(socket));
        }

    private:
        NetworkService &_ioContext;
        TCPAcceptor _acceptor;
        std::vector<std::unique_ptr<Server>> _sessions;
        uint16_t _port;
    };
}