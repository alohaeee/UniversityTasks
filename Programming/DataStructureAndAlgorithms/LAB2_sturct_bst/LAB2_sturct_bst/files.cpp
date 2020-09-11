#include "files.h"

dirfile::dirfile(const char* work_path, const char* finder) : workdir(work_path)
{
	for (const auto& entry : fl::directory_iterator(workdir)) {	//iterating all files in dir
		std::size_t txt_pos = entry.path().string().rfind(finder);  //finding typed format
		if (txt_pos != std::string::npos)		//if file with right format is existing
			path.push_back(entry.path().string()); //add to vector 
	}
}
void dirfile::menu(void)
{
	int i = 0;
	int c = 0;
	int flag = 0;
	std::cout << "Choose one to open." << std::endl
		<< "Txt files from work dir:" << std::endl;

	try {
		if (path.empty()) throw Myexception("No txt files in path", 1); //if our dir empty throw to exception and exit from programme
	}
	catch (Myexception & e)
	{
		throw;
	};
	for (const auto& str : path)
	{
		i++;
		std::size_t filename = str.rfind("\\"); // find last \ for clear output
		std::cout << i << ".\t" << str.substr(filename + 1) << std::endl;
		if (!flag && str.substr(filename + 1) == "FAQ.txt")
		{
			flag = i;
		}
	}

	while (true) //loop for choosing 
	{
		std::cout << "Num->";
		if (!(std::cin >> c)) //c is not digit
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
		from.open(path[c - 1]);//open choosed file
		if (from.is_open()) std::cout << "File was successfully open!" << std::endl;
		else throw Myexception("Failure to open file!", 3);
		if (c == flag)
		{
			std::cout << "\t FAQ" << std::endl;
			std::string s;
			while (!from.eof())
			{
				getline(from, s);
				std::cout << s << std::endl;
			}
			throw Myexception("Restart", 0);
		}
	}
	catch (Myexception & e)
	{
		throw;
	};
}


