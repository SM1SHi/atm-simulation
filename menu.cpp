#include <iostream>
#include <string>
#include "utils.h"

std::string menu() {
	uint8_t op;
	std::string loginID;
	do {
		std::cout << "Welcome, please select an option:" << std::endl;
		std::cout << "1. Register " << std::endl;
		std::cout << "2. Login" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "> ";
		std::cin >> op;
		
		switch (op) {
		case 1:
			std::cout << "Register selected." << std::endl;
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
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Wrong option, try again." << std::endl;
			}
			continue;
		}
		std::cout << std::endl;
		break;
	} while (true);
}
