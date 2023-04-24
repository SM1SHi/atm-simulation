#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <filesystem>

#include "utils.h"
// DEFINED IN defs.cpp, DECLARED in utils.h 
//const std::string filenames[] = { "_balance.txt", "_PIN.txt", "_history.txt" };
namespace fs = std::filesystem;

std::string confirmID() {
	std::string username;
	bool valid_username = false;

	while (!valid_username) {
		std::cout << "Enter your username: ";
		std::getline(std::cin, username);

		std::string dirstring = userdir;
		dirstring += username;

		fs::path userpath(dirstring);
		if (fs::is_directory(userpath)) {
			valid_username = true;
		}
		else {
			std::cout << "User does not exist! Please try again.\n";
		}
	}

	return username;
}

//confirmID returns ID arg for this 

// ako je hashovan string isti kao i onaj sto si dobio kada si procitao fajl nastavi
// ako hashovan string nije isti onda daj korisniku jos 3 pokusaja i posle toga terminisi program	
//loguj cinjenicu da je korisnik failovao 3 puta (moguci pokusaj provale pina)

std::string authenticateUser(std::string& ID) {
	unsigned static int count = 0;

	std::string PIN;
	std::string userpath;

	std::string dirstring = userdir;
	dirstring += ID;

	fs::path path(dirstring);
	fs::path path2(path / (ID + filenames[1]));

	std::ifstream pin_path(path2);
	std::string contents;

	if (pin_path.is_open()) {
		std::string line;
		while (std::getline(pin_path, line)) {
			contents += line;
		}
		pin_path.close();
	}
	// !!! BUG HIDDEN HERE 
	while(true) {
		PIN = sha256(inputPIN(PIN));
		if (PIN == contents) {
			LOG(ID, "Account access granted to user.");
			std::cout << "Access granted." << std::endl;
			return ID;
		}
		else {
			std::cout << "Wrong PIN." << std::endl;
			count++;
			if (count > 4) {
				LOG(ID, "PIN wrong too many times!");
				std::cout << "Too many attempts." << std::endl;
				std::cout << std::endl;
				break;
			}
			continue;
		}
	}
}

std::string login() {
	std::cout << "\nLogin to a user account" << std::endl;
	std::string loginID = confirmID();
	// next two lines must stay lol
	std::cin.ignore();
	std::cout.flush();
	std::cout << "You can enter your PIN now " << std::endl;
	loginID = authenticateUser(loginID);
	return loginID;
}

