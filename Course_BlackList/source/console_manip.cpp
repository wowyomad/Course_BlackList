#include "../include/console_manip.h"

Console::Console()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Update();
}

void Console::Update()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	GetConsoleScreenBufferInfo(handle, &csbi);

	size_x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	size_y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Console::SetWindow(short width, short height)
{
	COORD coord{ width, height };

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Right = width - 1;
	rect.Top = 0;
	rect.Bottom = height - 1;

	PCONSOLE_SCREEN_BUFFER_INFO csbi = new CONSOLE_SCREEN_BUFFER_INFO;
	GetConsoleScreenBufferInfo(handle, csbi);

	SetConsoleScreenBufferSize(handle, coord);
	SetConsoleWindowInfo(handle, true, &rect);
}

COORD Console::CoursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	
	return csbi.dwCursorPosition;
}

COORD Console::WindowSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	return csbi.dwSize;
}

COORD Console::GetWindowSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(HANDLE(STD_OUTPUT_HANDLE), &csbi);

	return csbi.dwSize;
}

COORD Console::GetCursourPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(HANDLE(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition;
}


void Console::cMove(short off_x, short off_y)
{
	COORD coord = CoursorPosition();
	coord.X += off_x;
	coord.Y = off_y;
	SetConsoleCursorPosition(handle, coord);
}

void Console::cMoveUp(unsigned short off)
{
	cMove(0, -off);
}

void Console::cMoveDown(unsigned short off)
{
	cMove(0, off);
}

void Console::cMoveLeft(unsigned short off)
{
	cMove(-off, 0);
}

void Console::cMoveRight(unsigned short off)
{
	cMove(off, 0);
}

void Console::cSet(short x, short y)
{
	SetConsoleCursorPosition(handle, { x, y });
}

void Console::CursourSet(short x, short y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

std::ostream& operator<<(std::ostream& os, COORD& coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coord.X, coord.Y });
	return os;
}

std::ostream& operator<<(std::ostream& os, COORD&& coord)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coord.X, coord.Y });
	return os;
}