#pragma once

#include <memory>
#include <functional>

#undef BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION
#undef BOOST_ASIO_HAS_BOOST_ASSERT
#undef BOOST_ASIO_HAS_BOOST_DATE_TIME
#undef BOOST_ASIO_HAS_BOOST_REGEX

#include "boost/asio.hpp"

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/placeholders.hpp"
#include "boost/bind.hpp"

constexpr int BUFFER_SIZE = 512;

class TCPAsyncSession
{
public:
	TCPAsyncSession(boost::asio::io_context &ioContext,
	                std::function<void(TCPAsyncSession *, char *)> &writeCallback,
	                std::function<void(TCPAsyncSession *, char *)> &readCallback)
		: _ioContext(ioContext), _tcpSocket(_ioContext),
		  _writeCallback(writeCallback), _readCallback(readCallback)
	{

	}

	void _readHandler(boost::system::error_code &errorCode, size_t bytesTransferred)
	{
		std::cout << _buffer << std::endl;
	}

	void start()
	{
		_tcpSocket.async_read_some(boost::asio::buffer(_buffer, 512),
		                           boost::bind(&TCPAsyncSession::_readHandler, this,
		                                       boost::asio::placeholders::error,
		                                       boost::asio::placeholders::bytes_transferred));

		/*        _tcpSocket.async_read_some(boost::asio::buffer(_buffer, sizeof(_buffer)),
										   boost::bind(
												   &TCPAsyncSession::_readHandler, this,
												   boost::asio::placeholders::error,
												   boost::asio::placeholders::bytes_transferred));
		*/    }

	boost::asio::ip::tcp::socket &socket()
	{
		return _tcpSocket;
	}

	std::function<void(TCPAsyncSession *session, char *)> &getReadCallback()
	{
		return _readCallback;
	}

	std::function<void(TCPAsyncSession *session, char *)> &getWriteCallback()
	{
		return _writeCallback;
	}

private:
	boost::asio::io_context &_ioContext;
	boost::asio::ip::tcp::socket _tcpSocket;
	char _buffer[BUFFER_SIZE]{0};

	std::function<void(TCPAsyncSession *session, char *)> &_writeCallback;
	std::function<void(TCPAsyncSession *session, char *)> &_readCallback;
};

class TCPAsyncServer
{
public:
	TCPAsyncServer(boost::asio::io_context &ioContext, int port)
		: _ioContext(ioContext), _endpoint(boost::asio::ip::tcp::v4(), port),
		  _acceptor(_ioContext, _endpoint)
	{
	}

	void accept()
	{
		std::shared_ptr<TCPAsyncSession> newSession = std::make_shared<TCPAsyncSession>(_ioContext, _writeCallback,
		                                                                                _readCallback);

		_acceptor.async_accept(newSession->socket(), std::bind(_acceptCallback, this, newSession));

		_clientSessions.push_back(newSession);
	}

	void
	setAcceptCallback(std::function<void(TCPAsyncServer *server, const std::shared_ptr<TCPAsyncSession> &)> &&callback)
	{
		_acceptCallback = std::move(callback);
	}

	void setWriteCallback(std::function<void(TCPAsyncSession *session, char *)> &&callback)
	{
		_writeCallback = std::move(callback);
	}

	void setReadCallback(std::function<void(TCPAsyncSession *session, char *)> &&callback)
	{
		_readCallback = std::move(callback);
	}

private:
	boost::asio::io_context &_ioContext;
	boost::asio::ip::tcp::endpoint _endpoint;
	boost::asio::ip::tcp::acceptor _acceptor;
	std::vector<std::shared_ptr<TCPAsyncSession>> _clientSessions;

	std::function<void(TCPAsyncServer *, const std::shared_ptr<TCPAsyncSession> &)> _acceptCallback{nullptr};
	std::function<void(TCPAsyncSession *session, char *)> _writeCallback;
	std::function<void(TCPAsyncSession *session, char *)> _readCallback;
};
