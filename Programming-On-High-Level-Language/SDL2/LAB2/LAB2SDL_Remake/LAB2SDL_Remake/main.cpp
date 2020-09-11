#include <iostream>
#include "Application.h"

constexpr auto TITLE = "Laboratornay rabota 2. Remake.";
constexpr auto WIDTH = 500;
constexpr auto HEIGHT = 500;

Application application(TITLE, WIDTH, HEIGHT);

int main(int argc, char* argv[])
{
	try {
		return application.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		application.destroy();
		return 1;
	}
	
} 