#pragma once
#include <iostream> 
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>
#include "Myexception.h"

namespace fl = std::experimental::filesystem;

class dirfile
{
public:
	std::ifstream from; //in file stream

private:
	std::vector<std::string> path; //pathes of txt files in graphes dir
	const fl::path workdir;
public:
	//append to vector path pathes of files ended with ".finder" 
	dirfile(const char* work_path, const char* finder);
	~dirfile(void) {
		from.close();
	};
	void menu(void);
};
