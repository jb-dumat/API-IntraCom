#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include "TcpSocket.hpp"
#include "Interpreter.hpp"

class ParocSession
{
public:
	ParocSession(std::shared_ptr<ISocket> &socket)
		: _socket(socket)
	{
		_socket->setReceive([&](const char *data, size_t size) { handleReceive(data, size); });

        _commandsMap.emplace("CONNECTION_ATTEMPT", std::bind(&ParocSession::connectionAttempt, this, std::placeholders::_1));
        _commandsMap.emplace("CONNECTION_SUCCESS", std::bind(&ParocSession::connectionSuccess, this, std::placeholders::_1));
        _commandsMap.emplace("CONNECTION_FAILED", std::bind(&ParocSession::connectionFailed, this, std::placeholders::_1));
        _commandsMap.emplace("END_CONNECTION", std::bind(&ParocSession::endConnection, this, std::placeholders::_1));
	}

	void handleReceive(const char *data, size_t size)
	{
		std::string msg(data, size);

		std::cout << "> Received msg: " << data << std::endl;

		Interpreter inter;
        auto args = inter.interpretPayload(msg);
        if (_commandsMap.find(args[1]) != _commandsMap.end()) {
            _commandsMap[args[1]](args);
        } else {
            //log this
            std::cout << "> " << args[1] << " command not found." << std::endl;
        }
	}

    using commandFunctor = std::function<int(const std::vector<std::string>& params)>;
    using commandTag = std::string;

    int connectionAttempt(const std::vector<std::string>& params)
    {
        //MAKE PAYLOAD
        std::cout << "> Sending msg: PAROC CONNECTION_SUCCESS" << std::endl;
        _socket->send("PAROC CONNECTION_SUCCESS");
        return 0;
    }

    int connectionSuccess(const std::vector<std::string>& params)
    {
        // Do something here
        std::cout << "> IHM Connection Established" << std::endl;
        return 0;
    }

    int connectionFailed(const std::vector<std::string>& params)
    {
        return 0;
    }

    int endConnection(const std::vector<std::string>& params)
    {
        _socket->send("PAROC END_CONNECTION");
        return 0;
    }

private:
    std::unordered_map<commandTag, commandFunctor> _commandsMap;
	std::shared_ptr<ISocket> _socket;
};
