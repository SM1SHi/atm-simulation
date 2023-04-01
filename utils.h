#pragma once
#include <string>

//defined in register.cpp
std::string sha256(const std::string str);
std::string maskpass(std::string& pass);
void registerUser();
std::string inputPIN(std::string& PINin);

//defined in login.cpp
std::string authenticateUser(std::string& ID);
std::string confirmID();
std::string login();
//add int option in args
void LOG(std::string& ID, std::string in1, std::string in2 = "", std::string in3 = "", std::string in4 = "");

//defined in menu.cpp
std::string menu();

//defined in transaction_processor.cpp
int checkAccountBalance(std::string& ID, int opt);
void transferAssets(std::string& ID);
std::string submenuLogin(std::string& ID);

extern std::string userdir;
extern const std::string filenames[3];
