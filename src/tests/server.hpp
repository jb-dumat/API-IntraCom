//
// Created by Jean-Baptiste Dumat on 05/02/2020.
//

#ifndef NEURACOM_SERVER_HPP
#define NEURACOM_SERVER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <neuracom/NetworkService.hpp>
#include <neuracom/Session.hpp>
#include <neuracom/SessionManager.hpp>
#include "config.hpp"

std::unordered_map<std::string, std::function<std::string(const std::vector<std::string>&)>> net::Session::SERVER_MAP;

using namespace std;

class TestServer {
public:
	using Parameters = std::vector<std::string>;

	TestServer()
			: _service(),
			  _server(_service, config::PORT) {
		net::Session::SERVER_MAP["ping"] = [&](const Parameters& args) {
			cout << "PING" << endl;
			return "pong";
		};

		net::Session::SERVER_MAP["test"] = [&](const Parameters& args) {
			cout << "TEST" << endl;
			return "success";
		};

		_server.setEventCb([&](const std::string& eventMsg) { cout << eventMsg << endl; });
		_server.launch();
		_service.run();
	}

private:
	net::NetworkService _service;
	net::SessionManager _server;
};

#endif //NEURACOM_SERVER_HPP
