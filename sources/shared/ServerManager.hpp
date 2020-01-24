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
        ServerManager(NetworkService &ioContext, int port)
                : _ioContext(ioContext), _acceptor(_ioContext) {
            _acceptor.bind(port);
            _acceptor.accept<TCPSocket>([&](std::shared_ptr<ISocket> socket) {
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
    };
}