#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdarg>

namespace net {
    using commandFunctor = std::function<std::string(const std::vector<std::string>& params)>;

    class Interpreter
    {
    public:
        explicit Interpreter(std::unordered_map<std::string, commandFunctor>& commandMap);
        ~Interpreter() = default;

        Interpreter() = delete;

        // Main functions
        static std::vector<std::string> stringToVector(const std::string &payload, char separator);

        static std::vector<std::string> parse(const std::string &str);

        std::string interpret(const std::vector<std::string>& args);

    private:
        std::unordered_map<std::string, commandFunctor>& _commandMap;
    };
}