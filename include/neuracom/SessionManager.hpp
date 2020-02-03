//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <memory>
#include <vector>

#include "NetworkService.hpp"
#include "TcpAcceptor.hpp"
#include "ISocket.hpp"
#include "Session.hpp"
#include <functional>

namespace net {
    class SessionManager {
    public:
        SessionManager(NetworkService &ioContext, uint16_t port)
                : _ioContext(ioContext), _acceptor(_ioContext), _port(port), _eventCb(nullptr)
        {
            _acceptor.bind(_port);
        }

        void launch() {
            _acceptor.accept<TCPSocket>([&](const std::shared_ptr<ISocket> &socket) {
                if (_eventCb)
                    _eventCb("Accepted new session: " + std::to_string(reinterpret_cast<long>(socket.get())));
                acceptSession(socket);
            });
        }

        void stop() {
            for (auto& session : _sessions) {
                if (_eventCb)
                    _eventCb("Stopping session: " +  std::to_string(reinterpret_cast<long>(session.get())));
                session->stop();
            }
            _acceptor.close();
        }

        void acceptSession(std::shared_ptr<ISocket> socket) {
            _sessions.emplace_back(new Session(socket, _eventCb));
        }

        void setEventCb(const std::function<void(const std::string& eventMsg)>& eventCb) {
            _eventCb = eventCb;
        }

        uint16_t getPort() {
            return _port;
        }

    private:
        NetworkService &_ioContext;
        TCPAcceptor _acceptor;
        std::vector<std::unique_ptr<Session>> _sessions;
        uint16_t _port;
        std::function<void(const std::string&)> _eventCb;
    };
}