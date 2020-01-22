#include <iostream>
#include "TcpAcceptor.hpp"

TCPAcceptor::TCPAcceptor(NetworkService &netService) : _netService(netService), _acceptor(_netService)
{

}

bool TCPAcceptor::bind(int port)
{
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	try {
		_acceptor.open(endpoint.protocol());
		_acceptor.set_option(
			boost::asio::ip::tcp::acceptor::reuse_address(true)); // REUSE // FOR DEBUG ONLY // DON T DELETE PLEASE <3
		_acceptor.bind(endpoint);
		_acceptor.listen();
	} catch (const std::runtime_error &error) {
		return false;
	}
	return true;
}