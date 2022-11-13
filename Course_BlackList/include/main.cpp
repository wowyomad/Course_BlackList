#include "Setup.hpp"
#include "RNG.hpp"

#include <iostream>
#include <conio.h>
#include "UserConsoleInput.h"
#include "../fff.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	foo();
	std::cout << "Вывод: " << InputPassword(8, 16);
	
}

