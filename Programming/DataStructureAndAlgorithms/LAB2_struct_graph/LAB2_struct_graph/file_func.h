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
	struct {
		size_t from;
		unsigned int width;
		size_t to;
	} road_data;
private:
	std::vector<std::string> path; //pathes of txt files in graphes dir
	const fl::path workdir;
	bool road_t = true;
public:
	//append to vector path pathes of files ended with ".finder" 
	dirfile(const char* work_path, const char* finder);
	~dirfile(void) {
		from.close();
	};
	
	bool road_type(void) { return road_t; };
	
	//read type of storage structure
	char read_type(void) 
	{
		char c;
		from.get(c);
		while (from.get() != '\n'); //get another part of line to move ptr 
		return c;
	};

	//read count of towns
	std::size_t count_town(void);

	bool read_road(void);
	
	void read_whole(void)
	{
		while (!from.eof())
		{
			std::string str;
			getline(from, str);
			std::cout << str << std::endl;
		}
	};


	//out to screen files and suggest to choose one
	void menu(void); 
};