#include <iostream>
#include <string>
#include "utils.h"

void menu() {
	uint32_t op;
	std::string loginID;
	do {
		std::cout << "Please select an option:" << std::endl;
		std::cout << "1. Register " << std::endl;
		std::cout << "2. Login" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "> ";
		std::cin >> op;
		
		switch (op) {
		case 1:
			std::cout << "Register selected." << std::endl;
			registerUser();
			continue;
		case 2:
			std::cout << "Login selected." << std::endl;
			loginID = login();
			do {
				std::cout << std::endl
					<< "Select option: " << std::endl
					<< "1. Check account balance" << std::endl
					<< "2. Transfer assets" << std::endl
					<< "3. Check account history" << std::endl
					<< "4. Return to previous menu" << std::endl;
					
				std::cout << "> ";
				unsigned int choice;
				std::cin >> choice;

				switch (choice) {
				case 1:
					checkAccountBalance(loginID, 1);
					continue;
				case 2:
					transferAssets(loginID);
					continue;
				case 3:
					std::cout << "not implemented yet" << std::endl;
					continue;
				case 4:
					break;
				}
			} while (true);
			break;
		case 3:
			std::cout << "exiting..." << std::endl;
			break;
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
