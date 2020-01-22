#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "NetworkService.hpp"
#include "TcpSocket.hpp"
#include "ClientManager.hpp"
#include "Interpreter.hpp"

#include <thread>

class Client
{
public:
	Client(NetworkService &ioContext, const std::string &ip, int port)
		: _ioContext(ioContext), _socket(_ioContext)
	{
		_socket.connect(port, ip);
		_socket.setReceive([&](const char *data, size_t size) { handleReceive(data, size); });

        _commandsMap.emplace("CONNECTION_ATTEMPT", std::bind(&Client::connectionAttempt, this, std::placeholders::_1));
        _commandsMap.emplace("CONNECTION_SUCCESS", std::bind(&Client::connectionSuccess, this, std::placeholders::_1));
        _commandsMap.emplace("CONNECTION_FAILED", std::bind(&Client::connectionFailed, this, std::placeholders::_1));
        _commandsMap.emplace("END_CONNECTION", std::bind(&Client::endConnection, this, std::placeholders::_1));

        std::cout << "> Sending CONNECTION_ATTEMPT" << std::endl;
	    _socket.send("IHM CONNECTION_ATTEMPT");
	}

	void handleReceive(const char *data, size_t size)
	{
		std::string msg(data, size);

		std::cout << "> Received msg: " << data << std::endl;

		// Interpret the response
		auto args = _inter.interpretPayload(msg);
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
        _socket.send("IHM CONNECTION_SUCCESS");
        return 0;
    }

    int connectionSuccess(const std::vector<std::string>& params)
    {
        // Do something here
        std::cout << "> PAROC Connection Established" << std::endl;
        return 0;
    }

    int connectionFailed(const std::vector<std::string>& params)
    {
        return 0;
    }

    int endConnection(const std::vector<std::string>& params)
    {
        std::cout << "> End of connection" << std::endl;
        return 0;
    }

private:
    std::unordered_map<commandTag, commandFunctor> _commandsMap;
	NetworkService &_ioContext;
	TCPSocket _socket;
	Interpreter _inter;
};
