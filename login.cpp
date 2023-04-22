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
	std::getline(std::cin, username);

	std::string dirstring = userdir;
	dirstring += username;

	fs::path userpath(dirstring);
	
	if (fs::is_directory(userpath)) {
		return username;
	}
	else {
		std::cout << "User does not exist! Try again.\n";
		return confirmID();  // Call confirmID recursively until a valid user is found
	}
}

//confirmID returns ID arg for this 

// ako je hashovan string isti kao i onaj sto si dobio kada si procitao fajl nastavi
// ako hashovan string nije isti onda daj korisniku jos 3 pokusaja i posle toga terminisi program	
//loguj cinjenicu da je korisnik failovao 3 puta (moguci pokusaj provale pina)
std::string authenticateUser(std::string& ID) {
	static int count = 0;
	count++;
	if (count >= 4) {
		LOG(ID, "PIN wrong too many times!");
		std::cout << "Too many attempts." << std::endl;
		std::cout << std::endl;
		menu(); 	
	}
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
	do {
		PIN = sha256(inputPIN(PIN));
		if (PIN == contents) {
			LOG(ID, "Account access granted to user.");
			std::cout << "Access granted." << std::endl;
			return ID;
		}
		else {
			std::cout << "Wrong PIN." << std::endl;
			authenticateUser(ID);
		}
	} while (true);
}

std::string login() {

	std::cout << "\nLogin to a user account" << std::endl;
	std::cout << "Please enter your full name: ";
	std::cin.ignore();
	std::cout.flush(); 
	std::string loginID = confirmID();
	
	std::cout << "You can enter your PIN now " << std::endl;
	std::cout << "> ";
	loginID = authenticateUser(loginID);

	
	return loginID;
}

