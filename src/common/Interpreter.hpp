#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstdarg>

class Interpreter
{
public:
	using pFunc = std::string (Interpreter::*)(const std::string &);

public:
	Interpreter();
	~Interpreter() = default;

	// Main functions
	void run();

	std::vector<std::string> stringToVector(const std::string &payload, char separator);

	std::vector<std::string> interpretPayload(const std::string &str);

	// Getters
	std::string getMsg();

private:
	std::map<std::string, pFunc> _funcMap;
	bool _running;
	std::string _msg;
};
