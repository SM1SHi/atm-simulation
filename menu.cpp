#include <iostream>
#include <string>
#include "utils.h"

std::string menu() {
	int op;
	do {
		std::cout << "Welcome, please select an option:" << std::endl;
		std::cout << "1. Register " << std::endl;
		std::cout << "2. Login" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "> ";
		std::cin >> op;
		std::string loginID;
		switch (op) {
		case 1:
			std::cout << "Register selected." << std::endl;
			std::cin.ignore();
			std::cout.flush();
			registerUser();
			break;
		case 2:
			std::cout << "Login selected." << std::endl;
			loginID = login();
			break;
		case 3:
			std::cout << "exiting..." << std::endl;
			exit(0);

		default:
			std::cout << "Wrong option, try again." << std::endl;
			break;
		}
		std::cout << std::endl;
	} while (op != 3);
}