#include "file_func.h"

//dirfile::dirfile(std::string work_path,std::string finder) : workdir(work_path)
dirfile::dirfile(const char* work_path, const char* finder) : workdir(work_path)
{
	for (const auto & entry : fl::directory_iterator(workdir)) {	//iterating all files in dir
		std::size_t txt_pos = entry.path().string().rfind(finder);  //finding typed format
		if (txt_pos != std::string::npos)		//if file with right format is existing
			path.push_back(entry.path().string()); //add to vector 
	}
}

std::size_t dirfile::count_town(void)
{
	std::string line;
	std::getline(from, line); 
	std::size_t towns = line.find("Towns:");
	try {
		if (towns == std::string::npos) throw Myexception("Wrong structure of txt file\nReduct and try again!", 2);
	}
	catch (Myexception &e)
	{
		throw;
	};
	std::stringstream count(line.substr(line.find(':')+1));
	while ((count >> towns));
	return towns;
}

bool dirfile::read_road(void)
{
	std::string path;
	getline(from, path);
	if (path == "Railway:")
		road_t = true;
	else if (path == "Highway:") {
		road_t = false;
	}
	else if (path == "");
	else {
		std::stringstream num(path);
		num >> road_data.from;
		num >> road_data.width;
		num >> road_data.to;
		road_data.from--;
		road_data.to--;
		return true;
	}
	return false;
}


void dirfile::menu(void)
{
	int i = 0;
	int c = 0;
	std::cout << "Choose one to open." << std::endl
		<< "Txt files from work dir:" << std::endl;

	try {
		if (path.empty()) throw Myexception("No txt files in path", 1); //if our dir empty throw to exception and exit from programme
	}
	catch (Myexception &e)
	{
		throw;
	};
	for (const auto& str : path)
	{
		i++;
		std::size_t filename = str.rfind("\\"); // find last \ for clear output
		std::cout << i << ".\t" << str.substr(filename + 1) << std::endl;
	}
	
	while (true) //loop for choosing 
	{
		std::cout << "Num->";
		if(!(std::cin >> c)) //c is not digit
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Wrong input!" << std::endl;
			continue;
		}
		if (c<1 || c>i) { // c is not in interval
			std::cerr << "No such file!" << std::endl;
		}
		else break;
		
	}

	try {
		from.open(path[c-1]); //open choosed file
		if (from.is_open()) std::cout << "File was successfully open!" << std::endl;
		else throw Myexception("Failure to open file!", 3);
	}
	catch (Myexception &e)
	{
		throw;
	};
}
