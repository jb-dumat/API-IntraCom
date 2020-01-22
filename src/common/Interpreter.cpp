#include <ctime>
#include "Interpreter.hpp"

/*
 * Constructors & Destructors
 */

Interpreter::Interpreter()
	: _running(true), _msg("PAROC CONNECTION_ATTEMPT")
{
}

/*
 * Main functions
 */

void Interpreter::run()
{
	std::string payload;

	while (_running) {
		getline(std::cin, payload);
		interpretPayload(payload);
	}
}

std::vector<std::string> Interpreter::stringToVector(const std::string &payload, char separator)
{
	std::vector<std::string> v;
	size_t found = payload.find_first_of(separator);
	size_t last_found = 0;

	while (found != std::string::npos) {
		v.push_back(payload.substr(last_found, found - last_found));
		last_found = found + 1;
		found = payload.find_first_of(separator, found + 1);
	}
	v.push_back(payload.substr(last_found, std::string::npos));

	return (v);
}

std::vector<std::string> Interpreter::interpretPayload(const std::string &str)
{
	return stringToVector(str, ' ');
}

/*
 * Getters
 */

std::string Interpreter::getMsg()
{
	return (_msg);
}