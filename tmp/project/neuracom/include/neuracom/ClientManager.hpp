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
                : _ioContext(ioContext) {}

        void newClient(const std::string ip, int port) {
            _clients.emplace_back(new Client(_ioContext, ip, port));
        }

    private:
        NetworkService &_ioContext;
        std::vector<std::unique_ptr<Client>> _clients;
    };
}