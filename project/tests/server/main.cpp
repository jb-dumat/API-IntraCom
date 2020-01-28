#include "Core.hpp"

int main(int argc, char* argv[])
{
	std::cout << "[PAROC] Starting..." << std::endl;
	try {
		paroc::Core core;

		core.run();
	} catch (const std::exception &e) {
	    std::cerr << e.what() << std::endl;
	    return 1;
	}
    return 0;
}
