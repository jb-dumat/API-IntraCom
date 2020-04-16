//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdarg>
#include <functional>
#include <boost/algorithm/string/predicate.hpp>

namespace net {
	using commandFunctor = std::function<std::string(const std::vector<std::string>& params)>;

	const char ARGUMENT_WRAPPER[] = "`";
	const unsigned int WRAPPER_LENGTH = std::strlen(ARGUMENT_WRAPPER);

	class Interpreter {
	public:
		explicit Interpreter(std::unordered_map<std::string, commandFunctor>& commandMap);

		~Interpreter() = default;

		Interpreter() = delete;

		// Methods
		std::string interpret(std::vector<std::string>&& args);

		// Static methods
		static std::vector<std::string> stringToVector(std::string&& payload);

		static std::vector<std::string> parse(std::string&& str);

		inline static std::string wrap(std::string&& arg) {
			return (arg.find(' ') != std::string::npos) ? ARGUMENT_WRAPPER + arg + ARGUMENT_WRAPPER : arg;
		}

		inline static std::string unwrap(std::string&& arg) {
			return (arg.rfind(ARGUMENT_WRAPPER, 0) == 0 && boost::algorithm::ends_with(arg, ARGUMENT_WRAPPER))
			       ? arg.substr(WRAPPER_LENGTH, arg.length() - WRAPPER_LENGTH * 2)
			       : arg;
		}

		template<typename ... Args>
		static std::string makePayload(const std::string& commandTag, Args&& ... args) {
			std::stringstream ss;

			ss << commandTag;
			std::initializer_list<int>{
					(ss << " " << formatPayload(args), 0)...
			};
			return ss.str();
		}

		template<typename T>
		static std::string formatPayload(T&& arg) {
			std::string str;
			std::stringstream ss;

			ss << arg;
			str = ss.str();
			return wrap(ss.str());
		}

	private:
		std::unordered_map<std::string, commandFunctor>& _commandMap;
	};
}