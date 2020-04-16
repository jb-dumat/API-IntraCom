//
// Created by Jean-Baptiste Dumat.
//

#include <iomanip>
#include "neuracom/Session.hpp"
#include "neuracom/Interpreter.hpp"

namespace net {
/*
 * Constructors & Destructors
 */
	Interpreter::Interpreter(std::unordered_map<std::string, commandFunctor>& commandMap)
			: _commandMap(commandMap)
	{}


/*
 * Main functions
 */
	std::vector<std::string> Interpreter::stringToVector(std::string&& payload) {
		std::istringstream iss(payload);
		std::vector<std::string> vec;
		std::string str;

		while (iss >> std::quoted(str, '`')) {
			vec.push_back(str);
		}

		return vec;
	}

	std::vector<std::string> Interpreter::parse(std::string&& str) {
		return stringToVector(std::forward<std::string>(str));
	}

	std::string Interpreter::interpret(std::vector<std::string>&& args) {
		const static std::string errResponse = "failure";

		if (!args.empty() && _commandMap.find(args.at(0)) != _commandMap.end()) {
			return _commandMap[args.at(0)](args);
		}

		return errResponse;
	}
}