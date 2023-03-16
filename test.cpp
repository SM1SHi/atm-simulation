#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

std::string registerID() {
    std::string name;
    std::cout << "Hello, please enter your name" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, name);
    return name;
}

namespace fs = std::filesystem;
std::string userdir = "./users/";

void createPath(std::string& ID) {
    
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
    ofs.close();
}


int main(){

    std::string ime = registerID();
    createPath(ime);
}
