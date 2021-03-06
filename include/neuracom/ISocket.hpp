//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <cstddef>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace net {
	constexpr size_t READ_SIZE = 1024;

	class ISocket {
	public:
		virtual ~ISocket() = default;

	public:
		virtual bool connect(uint16_t port, const std::string& ip) = 0;

		virtual void setReceive(const std::function<void(const char*, size_t)>&) = 0;

		virtual void setDisconnect(const std::function<void(ISocket*)>&) = 0;

		virtual void disconnect() = 0;

		virtual size_t send(const char*, size_t) = 0;

		virtual size_t send(const std::string&) = 0;

	private:
		virtual void handleReceive(const boost::system::error_code&, size_t) = 0;

		virtual void handleSend(const boost::system::error_code&) = 0;
	};
}