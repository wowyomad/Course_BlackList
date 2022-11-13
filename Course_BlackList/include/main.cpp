#include "Setup.hpp"
#include "RNG.hpp"

#include <iostream>
#include <conio.h>

#include <fcntl.h>
#include <io.h>


int main()
{
	/*SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	system("chcp 65001");
	setlocale(LC_ALL, "ru_RU.utf8");
	std::ios::sync_with_stdio(false);
	std::wcout.imbue(std::locale("ru_RU.utf8"));
	std::wcin.imbue(std::locale("ru_RU.utf8"));*/

	//std::cout.imbue(std::locale("ru_RU.utf8"));
	//std::cin.imbue(std::locale("ru_RU.utf8"));
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*SetConsoleOutputCP(65001);*/

	std::string aboba = "Сука блядскя";
	std::string test;
	std::cout << _getch() << _getch();
	std::cin >> test;
	std::cout << aboba << '\t' << test << '\n';/*
	if (aboba == test)
	{
		std::wcout << "Верно";
	}
	else
	{
		std::cout << "Неверно";
	}*/
}

