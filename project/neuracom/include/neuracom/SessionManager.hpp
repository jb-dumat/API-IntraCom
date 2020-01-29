#pragma once

#include <memory>
#include <vector>

#include "NetworkService.hpp"
#include "TcpAcceptor.hpp"
#include "ISocket.hpp"
#include "Session.hpp"

namespace net {
    class SessionManager {
    public:
        SessionManager(NetworkService &ioContext, uint16_t port)
                : _ioContext(ioContext), _acceptor(_ioContext), _port(port)
        {
            _acceptor.bind(_port);
        }

        void launch() {
            _acceptor.accept<TCPSocket>([&](const std::shared_ptr<ISocket> &socket) {
                std::cout << "Accepted new connection " << socket.get() << std::endl;
                acceptSession(socket);
            });
        }

        void stop() {
            for (auto& session : _sessions) {
                session->stop();
            }
            _acceptor.close();
        }

        void acceptSession(std::shared_ptr<ISocket> socket) {
            _sessions.emplace_back(new Session(socket));
        }

    private:
        NetworkService &_ioContext;
        TCPAcceptor _acceptor;
        std::vector<std::unique_ptr<Session>> _sessions;
        uint16_t _port;
    };
}