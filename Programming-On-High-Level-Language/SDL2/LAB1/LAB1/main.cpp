#include "Application.h"

constexpr auto TITLE = "Laboratornay rabota 1";
constexpr auto WIDTH = 500;
constexpr auto HEIGHT = 500;

Application apl(TITLE, WIDTH, HEIGHT);

int main(int argc, char* argv[])
{
	return apl.run();
} 