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

    std::vector<std::string> Interpreter::stringToVector(const std::string &payload) {
        std::istringstream iss(payload);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());

        return results;
    }

    std::vector<std::string> Interpreter::parse(const std::string &str) {
        return stringToVector(str);
    }

    std::string Interpreter::interpret(const std::vector<std::string> &args) {
        const static std::string errResponse = "No command found";

        if (args.size() >= 1 && _commandMap.find(args[1]) != _commandMap.end()) {
            return _commandMap[args[1]](args);
        }
        return errResponse;
    }
}