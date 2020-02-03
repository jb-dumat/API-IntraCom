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

    class Interpreter
    {
    public:
        explicit Interpreter(std::unordered_map<std::string, commandFunctor>& commandMap, bool caseInsensitive = true);
        ~Interpreter() = default;

        Interpreter() = delete;

        static std::vector<std::string> stringToVector(std::string&& payload);

        static std::vector<std::string> parse(std::string&& str);

        std::string interpret(std::vector<std::string>&& args);

    private:
        std::unordered_map<std::string, commandFunctor>& _commandMap;
        bool _caseInsensitive;
    };
}