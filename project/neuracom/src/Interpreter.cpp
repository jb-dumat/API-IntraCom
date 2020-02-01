//
// Created by Jean-Baptiste Dumat.
//

#include <neuracom/Session.hpp>
#include "neuracom/Interpreter.hpp"

namespace net {
/*
 * Constructors & Destructors
 */
    Interpreter::Interpreter(std::unordered_map<std::string, commandFunctor> &commandMap, bool caseInsensitive)
            : _commandMap(commandMap), _caseInsensitive(caseInsensitive)
    {
    }

/*
 * Main functions
 */
    std::vector<std::string> Interpreter::stringToVector(std::string&& payload) {
        std::istringstream iss(payload);
        return std::vector<std::string>(std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>());
    }

    std::vector<std::string> Interpreter::parse(std::string&& str) {
        return stringToVector(std::forward<std::string>(str));
    }

    std::string Interpreter::interpret(std::vector<std::string>&& args) {
        const static std::string errResponse = "No command found";

        if (_caseInsensitive && !args.empty()) {
            std::transform(args.front().begin(), args.front().end(), args.front().begin(),
                    [](unsigned char c) { return std::tolower(c); });
        }

        if (!args.empty() && _commandMap.find(args.at(0)) != _commandMap.end()) {
            return _commandMap[args.at(0)](args);
        }
        return errResponse;
    }
}