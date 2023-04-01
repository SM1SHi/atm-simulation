#pragma once
#include <string>
std::string sha256(const std::string str);
std::string maskpass(std::string& pass);
void usrinputStats();
extern std::string userdir;
extern const std::string filenames[3];
