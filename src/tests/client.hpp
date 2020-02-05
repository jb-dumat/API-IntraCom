//
// Created by Jean-Baptiste Dumat on 05/02/2020.
//

#ifndef NEURACOM_CLIENT_HPP
#define NEURACOM_CLIENT_HPP

#include <neuracom/NetworkService.hpp>
#include <neuracom/ClientManager.hpp>
#include <neuracom/Client.hpp>
#include <vector>
#include <string>
#include "config.hpp"

std::unordered_map<std::string, std::function<std::string(const std::vector<std::string>&)>> net::Client::CLIENT_MAP;

using namespace std;

class TestClient {
public:
    using Paramters = std::vector<std::string>;
    TestClient()
        : _service(),
          _client(_service)
    {
        _client.setEventCb([&](const std::string& eventMsg) { cout << eventMsg << endl; });
        net::Client* client = _client.newClient(config::IP, config::PORT);

        net::Client::CLIENT_MAP["success"] = [&](const Paramters& args) { cout << "Connected" << endl; return ""; };

        client.

        _service.run();
    }

private:
    net::NetworkService _service;
    net::ClientManager _client;
};

#endif //NEURACOM_CLIENT_HPP