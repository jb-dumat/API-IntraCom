//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <utility>

#include "NetworkService.hpp"
#include "TcpSocket.hpp"
#include "Interpreter.hpp"

namespace net {
	constexpr unsigned int CONNECTION_LOOP_DURATION_MS = 50;

	class Client {
	public:
		explicit Client(NetworkService& ioContext, const std::string& ip, uint16_t port, bool waitConnection = true)
				: _ioContext(ioContext), _socket(_ioContext), _interpreter(CLIENT_MAP), _eventCb(nullptr) {
			if (waitConnection)
				this->loopUntilConnected(ip, port);
			_socket.setReceive([&](const char* data, size_t size) { handleReceive(data, size); });
		}

		explicit Client(NetworkService& ioContext, const std::string& ip, uint16_t port,
						std::function<void(const std::string&)>&& eventCb, bool waitConnection = true)
				: _ioContext(ioContext), _socket(_ioContext), _interpreter(CLIENT_MAP), _eventCb(std::move(eventCb)) {
			if (waitConnection)
				this->loopUntilConnected(ip, port);
			_socket.setReceive([&](const char* data, size_t size) { handleReceive(data, size); });
		}

		void handleReceive(const char* data, size_t size) {
			std::string msg(data, size);

			if (_eventCb)
				_eventCb("Received msg: " + msg);

			// Interpret the response
			auto&& args = net::Interpreter::parse(std::move(msg));
			auto&& response = _interpreter.interpret(std::move(args));

			if (response == "success")
				return;
			else if (response == "failure") {
				if (_eventCb)
					_eventCb("FAILURE");
				return;
			}

			if (_eventCb)
				_eventCb("Send msg: " + response);

			_socket.send(response);
		}

		inline void manualSend(const std::string& msg) {
			_socket.send(msg);
		}

		template<typename ... Args>
		inline void manualSend(const std::string& commandName, Args&& ... args) {
			_socket.send(_interpreter.makePayload(commandName, args...));
		}

		static std::unordered_map<std::string, commandFunctor> CLIENT_MAP;

	private:
		void loopUntilConnected(const std::string& ip, uint16_t port) {
			while (!_socket.connect(port, ip)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(CONNECTION_LOOP_DURATION_MS));
			}
		}

		NetworkService& _ioContext;
		TCPSocket _socket;
		Interpreter _interpreter;
		std::function<void(const std::string&)> _eventCb;
	};
}