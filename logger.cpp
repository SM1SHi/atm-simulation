#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "utils.h"

namespace fs = std::filesystem;

std::string writeTime() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* tm = std::localtime(&now);
	std::ostringstream oss;
	oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
	std::string current_time = oss.str();
	return current_time;
}
//add int option in args
void LOG(std::string& ID, std::string in1, std::string in2 , std::string in3, std::string in4) {
	std::string dirstring = userdir;
	dirstring += ID;
	
	fs::path path(dirstring);
	fs::path path2(path / (ID + filenames[2]));
	std::ofstream ofs(path2,std::ios::app);
	std::string current_time = writeTime();
	ofs << current_time + " " + in1 + " " + in2 + " " + in3 + in4 << std::endl;
	ofs.close();
}