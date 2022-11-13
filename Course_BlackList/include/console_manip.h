#include <Windows.h>

#include <iostream>

class Console
{
	HANDLE handle;
	COORD coursor_position;
	int size_x, size_y;


public:
	Console();

	void Update();

	void SetWindow(short width, short height);
	


	COORD CoursorPosition();
	COORD WindowSize();

	static COORD GetWindowSize();
	static COORD GetCursourPosition();

	void cMove(short off_x, short off_y);
	

	void cMoveUp(unsigned short off);
	void cMoveDown(unsigned short off);
	void cMoveLeft(unsigned short off);
	void cMoveRight(unsigned short off);

	void cSet(short x, short y);
	static void CursourSet(short x, short y);
};


class Cursour
{
	short X;
	short Y;

public:
	Cursour(short X, short Y) : X(X), Y(Y) {}

	void Move(short X, short Y)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO cbsi;
		GetConsoleScreenBufferInfo(handle, &cbsi);
		cbsi.dwCursorPosition.X += X;
		cbsi.dwCursorPosition.Y += Y;
		SetConsoleCursorPosition(handle,  {X, Y});
	}

	Cursour operator()(short X, short Y)
	{
		this->X = X;
		this->Y = Y;
		return *this;
	}

	static COORD GetCursour()
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO cbsi;
		GetConsoleScreenBufferInfo(handle, &cbsi);
		return  cbsi.dwCursorPosition;
	}

	friend std::ostream& operator<<(std::ostream& os, Cursour& c)
	{
		c.Move(c.X, c.Y);
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, Cursour&& c)
	{
		c.Move(c.X, c.Y);
		return os;
	}
};

std::ostream& operator<<(std::ostream& os, COORD& coord);

std::ostream& operator<<(std::ostream& os, COORD&& coord);