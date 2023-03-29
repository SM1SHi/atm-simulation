#pragma once
#include <string>
std::string sha256(const std::string str);
std::string maskpass(std::string& pass);
extern std::string userdir;
extern std::string filenames[3];