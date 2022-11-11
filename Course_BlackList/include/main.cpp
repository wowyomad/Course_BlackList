#include <iostream>
#include <string>

#include "common.h"
#include "Money.hpp"

#include <Windows.h>

#include <conio.h>

void gotoxy(COORD pos)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

COORD getxy()
{
	COORD pos;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(output, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		throw std::exception("Не получилось поработать с курсором");
	}
}

enum class SIGN
{
	positive = '\0',
	negative = '-'
};


int main()
{
	gotoxy({ 5, 5 });
	std::cout << "Hello World\n";
	gotoxy({ 0, 0 });
	std::cout << "No, u!\n";
	gotoxy({ 10,10 });
}
