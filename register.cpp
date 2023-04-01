#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <thread>
#include <chrono>
#include <future>

#include "utils.h"

//sha256 implementation, works good 
std::string sha256(const std::string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}


// !!! FIX USER CANNOT ENTER SPACE OR RETURN AS A FIRST CHARACTER 
std::string registerID() {
    std::string name;
    std::cout << "Hello, please enter your name" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, name);
    return name;
}

namespace fs = std::filesystem;

// creates folder named after ID, with needed files 

void createPath(std::string& ID, int& BAL, std::string& PIN) {
    //below are declared in "utils.h" and defined in "defs.cpp" 
    //extern std::string userdir = "./users/";
    //extern const std::string filenames[] = { "_balance.txt", "_PIN.txt", "_history.txt" };
    std::string dirstring = userdir;
    dirstring += ID;

    fs::path path(dirstring);
    path /= ID;
    std::ofstream ofs(path);

    fs::path userpath(dirstring);
    fs::create_directories(userpath);

    for (const auto& filename : filenames) {
        fs::path filepath(userpath / (ID + filename));
        std::ofstream ofs(filepath);   
    }
 
    //actually readable now
    fs::path balance_path(userpath / (ID + filenames[0]));
    std::ofstream balance_ofs(balance_path);
    balance_ofs << BAL << std::endl;
    balance_ofs.close();

    fs::path pin_path(userpath / (ID + filenames[1]));
    std::ofstream pin_ofs(pin_path);
    pin_ofs << PIN << std::endl;
    pin_ofs.close();

    ofs.close();
}

//masks PIN input with * 
std::string maskpass(std::string& pass) {
    char c;
    while ((c = _getch()) != '\r') {
        if (c == '\b' && !pass.empty()) {
            pass.pop_back();
            std::cout << "\b \b";
        }
        else {
            pass.push_back(c);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return pass;
}

std::string inputPIN(std::string& PINin) {
    PINin = maskpass(PINin);
    
    for (char& c : PINin) {
        if (!std::isdigit(c)) {
            PINin = "";
            std::cout << "Invalid input. Please enter numerical values only." << std::endl;
            std::cout << "> ";
            inputPIN(PINin);
        }
        else if (PINin.length() < 4) {
            PINin = "";
            std::cout << "PIN must consist of 4 numbers minimum. " << std::endl;
            std::cout << "> ";
            inputPIN(PINin);
        }
    }

    if (PINin._Starts_with("0")) {
        PINin = "";
        std::cout << "PIN must not start with 0" << std::endl;
        std::cout << "> ";
        inputPIN(PINin);
    }
    return PINin;
}

// BALLIN() was sacrificed for the sake of readability :(
int inputBAL(int& BALin) {
    std::cout << "Balance (EUR): ";
    std::cin >> BALin;

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter numerical values only." << std::endl;
        inputBAL(BALin);
    }

    return BALin;
}


void usrinputStats() {
    std::string usr_name = registerID();
    std::string  PIN;
    int balance;

    std::cout << "Please enter account stats: " << std::endl;
    balance = inputBAL(balance);

    std::cout << "Enter the PIN you want to set: " << std::endl;
    PIN = sha256(inputPIN(PIN));

    createPath(usr_name, balance, PIN);
    std::exit(0);
}


