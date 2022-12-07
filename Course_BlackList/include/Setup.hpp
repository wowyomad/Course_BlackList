#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>

#include "RNG.hpp"
#include "console_manip.h"

#include <assert.h>
void Setup()
{
	using namespace std::filesystem;

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	const char FILES_PATH[] = "Files";

	if (!exists(FILES_PATH))
	{
		if (!create_directories(FILES_PATH))
		{
			assert(("��� ������� � ������/������."));
		}
	}
	std::filesystem::current_path(FILES_PATH);

	std::cout << current_path() << '\n';


}