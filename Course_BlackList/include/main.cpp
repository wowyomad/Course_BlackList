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
	;*/

	/*std::ios::sync_with_stdio(false);
	std::wcout.imbue(std::locale("ru_RU.utf8"));
	std::wcin.imbue(std::locale("ru_RU.utf8"));*/

	//setlocale(LC_ALL, "Russian"); // задаём русский текст
	//system("chcp 1251");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*SetConsoleOutputCP(65001);*/

	std::string aboba = "сука";
	std::string test;
	std::cout << _getch() << _getch();
	std::cin >> test;
	std::cout << aboba << '\t';
	std::cout << test << '\n';
}

