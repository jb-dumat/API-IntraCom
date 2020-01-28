#include <iostream>
#include "neuracom/NetworkService.hpp"
#include "neuracom/ClientManager.hpp"

int main(int argc, char *argv[])
{
    std::cout << "[IHM] Starting..." << std::endl;

	try {
        net::NetworkService service;
        net::ClientManager manager(service);

        manager.newClient("127.0.0.1", 4242);

        service.run();

	} catch (const std::exception &e) {
	    std::cerr << e.what() << std::endl;
	    return 1;
	}
    return 0;
}
