//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <regex>

#include "TcpSocket.hpp"
#include "Interpreter.hpp"

namespace net {
	class Session {
	public:
		explicit Session(std::shared_ptr<ISocket>& socket)
				: _socket(socket), _interpreter(SERVER_MAP), _eventCb(nullptr) {
			_socket->setReceive([&](const char* data, size_t size) { readPayload(data, size); });
			_socket->setDisconnect([&](net::ISocket*) { this->stop(); });
		}

		explicit Session(std::shared_ptr<ISocket>& socket, std::function<void(const std::string&)> eventCb)
				: _socket(socket), _interpreter(SERVER_MAP), _eventCb(std::move(eventCb)) {
			_socket->setReceive([&](const char* data, size_t size) { readPayload(data, size); });
			_socket->setDisconnect([&](net::ISocket*) { this->stop(); });
		}

		void readPayload(const char* data, size_t size) {
			std::string msg(data, size);

			if (_eventCb) {
				msg = std::regex_replace(msg, std::regex("\n"), "");
				_eventCb("Session " + std::to_string(reinterpret_cast<long>(_socket.get())) + " received: '" + msg +
						 "'");
			}

			auto&& args = net::Interpreter::parse(std::move(msg));
			std::string&& response = _interpreter.interpret(std::move(args));

			// Any cleaner solution ?
			if (response == "disconnect") {
				this->shutdownStream();
				return;
			} else if (response == "success") {
				return;
			} else if (response == "failure") {
				if (_eventCb) {
					_eventCb("FAILURE");
				}
				return;
			}

			// Log response
			_socket->send(response);

			if (_eventCb) {
				_eventCb("Session " + std::to_string(reinterpret_cast<long>(_socket.get())) + " sent: '" + response +
						 "'");
			}
		}

		void shutdownStream() {
			// Log something
			dynamic_cast<TCPSocket*>(_socket.get())->get().shutdown(boost::asio::socket_base::shutdown_both);
		}

		void stop() {
			_eventCb("Session " + std::to_string(reinterpret_cast<long>(_socket.get())) + " has disconnected");
		}

		void manualSend(const std::string& msg) {
			_socket->send(msg);
		}

		template<typename ... Args>
		void manualSend(const std::string& commandName, Args&& ... args) {
			_socket->send(_interpreter.makePayload(commandName, args...));
		}

		static std::unordered_map<std::string, net::commandFunctor> SERVER_MAP;

	private:
		std::shared_ptr<ISocket> _socket;
		Interpreter _interpreter;
		std::function<void(const std::string&)> _eventCb;
	};
}