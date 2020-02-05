//
// Created by Jean-Baptiste Dumat on 05/02/2020.
//

#ifndef NEURACOM_SERVER_HPP
#define NEURACOM_SERVER_HPP

#include <neuracom/NetworkService.hpp>
#include <neuracom/SessionManager.hpp>
#include <neuracom/Session.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "config.hpp"

std::unordered_map<std::string, std::function<std::string(const std::vector<std::string>&)>> net::Session::SERVER_MAP;

using namespace std;

class TestServer {
public:
    using Parameters = std::vector<std::string>;
    TestServer()
        : _service(),
          _server(_service, config::PORT)
    {
        net::Session::SERVER_MAP["connection"] =  [&](const Parameters& args) { cout << "Connection..." << endl; return "success"; };
        net::Session::SERVER_MAP["ping"] =  [&](const Parameters& args) { cout << "Ping..." << endl; return "pong"; };

        _server.setEventCb([&](const std::string& eventMsg) { cout << eventMsg << endl; });
        _service.run();
    }

private:
    net::NetworkService _service;
    net::SessionManager _server;
};

#endif //NEURACOM_SERVER_HPP
