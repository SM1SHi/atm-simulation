#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "utils.h"

namespace fs = std::filesystem;

int checkAccountBalance(std::string& ID, int opt) {
	std::string acc_stats;
	std::string dirstring = userdir;
	dirstring += ID;
	
	fs::path path(dirstring);
	fs::path path2(path / (ID + filenames[0]));

	std::ifstream bal_path(path2);
	std::string contents;
	if (bal_path.is_open()) {
		std::string line;
		while (std::getline(bal_path, line)) {
			contents += line;
		}
		bal_path.close();
	}
	int num = std::stoi(contents);
	if (opt == 1) {
		std::cout << num << std::endl;
	}
	else {
		return num;
	}
}

std::string submenuLogin(std::string& ID) {
	int op;
	std::cout << "Successfully logged in." 
		<< "Select option: " << std::endl
		<< "1. Check account balance" << std::endl
		<< "2. Transfer assets" << std::endl
		<< "3. Check account history" << std::endl;
	std::cout << "> ";
	std::cin >> op;
	switch (op) {
	case 1:
		checkAccountBalance(ID, 1);
		submenuLogin(ID);
		break;

	case 2:
		transferAssets(ID);
		std::cin.ignore();
		std::cout.flush();
		submenuLogin(ID);
		break;

	case 3:
		std::cout << "not implemented yet" << std::endl;
		submenuLogin(ID);
		break;
	}
	return ID;
}

void transferAssets(std::string& ID) {
	unsigned int balance = checkAccountBalance(ID, 0);
	unsigned int to_transfer;

	std::cout << balance << std::endl;
	std::cout << "Please enter how much you want to transfer: " << std::endl;
	std::cin >> to_transfer;

	balance = balance - to_transfer;
	std::cout << "Enter the recipients name: ";
	
	if (to_transfer > balance) {
		std::cout << "You cannot transfer more assets than you currently possess" << std::endl;
		std::cin.ignore();
		std::cout.flush();
		transferAssets(ID);
	}

	std::cin.ignore();
	std::cout.flush();

	std::string recipient;
	std::getline(std::cin, recipient);

	//add option to actually send money to recipient
	std::cout << "Successfully sent " << to_transfer << " EUR" << " to " << recipient << std::endl;
	std::string str = std::to_string(to_transfer);
	LOG(ID, "You sent ", str," to ", recipient);

}