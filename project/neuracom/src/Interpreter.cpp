#include <ctime>
#include "../include/Interpreter.hpp"

namespace net {
/*
 * Constructors & Destructors
 */
    Interpreter::Interpreter(std::unordered_map<std::string, commandFunctor> &commandMap)
            : _commandMap(commandMap) {}

/*
 * Main functions
 */

    std::vector<std::string> Interpreter::stringToVector(const std::string &payload, char separator) {
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

    std::vector<std::string> Interpreter::parse(const std::string &str) {
        return stringToVector(str, ' ');
    }

    std::string Interpreter::interpret(const std::vector<std::string> &args) {
        const static std::string errResponse = "No command found";

        if (_commandMap.find(args[0]) != _commandMap.end()) {
            return _commandMap[args[0]](args);
        }
        return errResponse;
    }
}