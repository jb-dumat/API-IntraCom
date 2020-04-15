//
// Created by Jean-Baptiste Dumat on 05/02/2020.
//

#include <iostream>

#include "server.hpp"

using namespace std;

int main() {
	cout << "Test server: " << endl;

	try {
		TestServer server;

	} catch (const std::exception& e) {
		cerr << "Runtime error: " << e.what() << endl;
	}

	return 0;
}