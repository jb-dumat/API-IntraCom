//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdarg>
#include <functional>

namespace net {
	using commandFunctor = std::function<std::string(const std::vector<std::string>& params)>;

	constexpr std::string_view ARGUMENT_WRAPPER_DEFAULT = "`";

	class Interpreter {
	public:
		explicit Interpreter(std::unordered_map<std::string, commandFunctor>& commandMap,
		                     const std::string_view& wrapper = ARGUMENT_WRAPPER_DEFAULT);

		~Interpreter() = default;

		Interpreter() = delete;

		static std::vector<std::string> stringToVector(std::string&& payload);

		static std::vector<std::string> parse(std::string&& str);

		std::string interpret(std::vector<std::string>&& args);

	private:
		std::unordered_map<std::string, commandFunctor>& _commandMap;
		const std::string_view _wrapper;
	};
}