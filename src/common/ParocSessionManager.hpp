#pragma once

#include <memory>
#include <vector>

#include "NetworkService.hpp"
#include "TcpAcceptor.hpp"
#include "ISocket.hpp"
#include "ParocSession.hpp"

class ParocSessionManager
{
public:
	ParocSessionManager(NetworkService &ioContext, int port)
		: _ioContext(ioContext), _acceptor(_ioContext)
	{
		_acceptor.bind(port);
		_acceptor.accept<TCPSocket>([&](std::shared_ptr<ISocket> socket) {
			std::cout << "Accepted new connection " << socket.get() << std::endl;
			acceptSession(socket);
		});

	}

	void acceptSession(std::shared_ptr<ISocket> socket)
	{
		_sessions.emplace_back(new ParocSession(socket));
	}

private:
	NetworkService &_ioContext;
	TCPAcceptor _acceptor;
	std::vector<std::unique_ptr<ParocSession>> _sessions;
};
