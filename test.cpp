#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <conio.h>

std::string registerID() {
    std::string name;
    std::cout << "Hello, please enter your name" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, name);
    return name;
}

namespace fs = std::filesystem;
std::string userdir = "./users/";

void createPath(std::string& ID, std::string& BAL, std::string& PIN) {
    
    userdir += ID;

    fs::path path(userdir);
    path /= ID;
    std::ofstream ofs(path);

    fs::path userpath(userdir);
    fs::create_directories(userpath);

    std::string filenames[] = { "_balance.txt", "_PIN.txt", "_history" };
    for (const auto& filename : filenames) {
        fs::path filepath(userpath / (ID + filename));
        std::ofstream ofs(filepath);
        
    }

    //write to balance and PIN, history not yet used
    for (int i = 0; i <= 1; ++i) {
        fs::path path(userpath / (ID + filenames[i]));
        std::ofstream ofs(path);

    }

    fs::path balance_path(userpath / (ID + filenames[0]));
    std::ofstream balance_ofs(balance_path);
    balance_ofs << BAL << std::endl;

    fs::path pin_path(userpath / (ID + filenames[1]));
    std::ofstream pin_ofs(pin_path);
    pin_ofs << PIN << std::endl;


    ofs.close();
}

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

int usrinputStats() {
    std::string usr_name = registerID();
    std::string balance, PIN;
    std::cout << "Please enter your current account stats: " << std::endl;
    std::cout << "Balance: " << std::endl;
    std::cin >> balance;

    for (char& c : balance) {
        if (!std::isdigit(c)) {
            std::cout << "Invalid input. Please enter numerical values only." << std::endl;
            return 1;
        }
    }

    std::cout << "Enter the PIN you want to set: " << std::endl;
    PIN = maskpass(PIN);
    
    for (char& c : PIN) {
        if (!std::isdigit(c)) {
            std::cout << "Invalid input. Please enter numerical values only." << std::endl;
            return 1;
        }
        else if (PIN.length() < 4) {
            std::cout << "PIN must consist of 4 numbers minimum. " << std::endl;
            return 1;
        }
    }
    
    createPath(usr_name, balance, PIN);
    
}





int main(){

    usrinputStats();
   
}
