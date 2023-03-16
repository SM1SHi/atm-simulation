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

void createPath(std::string& ID) {
   
    std::string userid = "./users/";
    userid += ID;
    
    // ADD THIS --------------------------------{}{}{}{}{}{}{}{}{}
    //create files in folder /user_name/ --> history, PIN, balance
   
    std::filesystem::path path(userid);
    path /= ID + "_balance.txt"; 
    std::filesystem::create_directories(path.parent_path()); 
    std::ofstream ofs(path, std::ios_base::app);
    ofs << "1. this is some text in the new file\n" + ID + "\n";
    ofs.close();
}

int main(){

    std::string ime = registerID();
    createPath(ime);
}
