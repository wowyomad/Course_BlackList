#include "Setup.hpp"
#include "RNG.hpp"
#include "UserConsoleInput.h"

#include "console_manip.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	tm tm = InputDate();
	std::cout << '\n';
	std::cout << std::put_time(&tm, "%d.%m.%Y");
}

