//
// Created by Jean-Baptiste Dumat on 05/02/2020.
//

#include <iostream>

#include "client.hpp"

using namespace std;

int main() {
    cout << "Test client: " << endl;

    try {
        TestClient client;

    } catch ( const std::exception& e) {
        cerr << "Runtime error: " << e.what() << endl;
    }

    return 0;
}