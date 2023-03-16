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

void createPath(std::string& ID) {
    
    std::string userdir = "./users/";
    userdir += ID;

    fs::path path(userdir);
    path /= ID;
    std::ofstream ofs(path);

    std::string filenames[] = { "_balance.txt", "_PIN.txt", "_history" };
    for (const auto& filename : filenames) {
        path += filename;
        fs::create_directories(path.parent_path());
        std::ofstream ofs(path);

    }
    ofs.close();
}

int main(){

    std::string ime = registerID();
    createPath(ime);
}
