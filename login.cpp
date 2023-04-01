#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

#include "utils.h"
// DEFINED IN defs.cpp, DECLARED in utils.h 
//const std::string filenames[] = { "_balance.txt", "_PIN.txt", "_history.txt" };
namespace fs = std::filesystem;

std::string confirmID() {
	std::string username;

	std::cout << "\nLogin to a user account" << std::endl;
	std::cout << "Please enter your full name: ";

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
void authenticateUser(std::string& ID) {
	static int count = 0;
	count++;
	if (count >= 4) {
		std::cout << "Too many attempts." << std::endl;
		exit(0); //!!! maybe prompt user to beginning of the program 
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

	PIN = sha256(inputPIN(PIN));
	if (PIN == contents) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "nope..." << std::endl;
		authenticateUser(ID);
	}

	std::cout << PIN;
}
