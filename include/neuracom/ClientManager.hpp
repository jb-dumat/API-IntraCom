//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Client.hpp"
#include "NetworkService.hpp"
#include "TcpSocket.hpp"

namespace net {
    class ClientManager {
    public:
        ClientManager(NetworkService &ioContext)
                : _ioContext(ioContext), _eventCb(nullptr)
        {

        }

        Client* newClient(const std::string& ip, int port)
        {
            _clients.emplace_back(new Client(_ioContext, ip, port, _eventCb));
            return _clients.back().get();
        }

        void setEventCb(const std::function<void(const std::string& eventMsg)>& eventCb)
        {
            _eventCb = eventCb;
        }

    private:
        NetworkService &_ioContext;
        std::vector<std::unique_ptr<Client>> _clients;
        std::function<void(const std::string&)> _eventCb;
    };
}