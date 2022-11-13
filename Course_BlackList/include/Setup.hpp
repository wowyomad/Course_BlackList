#include <Windows.h>
#include <direct.h>
#include <iostream>

#include "RNG.hpp"
#include "console_manip.h"

void Setup()
{
	_mkdir("Files");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	Console console;

}