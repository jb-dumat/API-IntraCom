#pragma once

#include <iostream>
#include <string>
#include "utils/ConfigLoader.hpp"
#include "common/NetworkService.hpp"
#include "common/ParocSessionManager.hpp"

static const std::string configFilePath = "./config.yml";


namespace paroc {

class Core
{
public:
	Core()
		: _config(configFilePath), _port(_config["port"].as<int>()), _service(), _manager(_service, _port)
	{}
	~Core() = default;

	void run()
	{
		std::cout << "Listening on port " << _port << "..." << std::endl;
		_service.run();
	}

	// Getters
	inline int getPort() { return _port; }

private:
	ConfigLoader _config;
	int _port;
	NetworkService _service;
	ParocSessionManager _manager;
};

}
