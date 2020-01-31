#include <ctime>
#include <neuracom/Session.hpp>
#include "neuracom/Interpreter.hpp"

namespace net {
/*
 * Constructors & Destructors
 */
    Interpreter::Interpreter(std::unordered_map<std::string, commandFunctor> &commandMap)
            : _commandMap(commandMap) {
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

        if (!args.empty() && _commandMap.find(args[0]) != _commandMap.end()) {
            return _commandMap[args[0]](args);
        }
        return errResponse;
    }
}