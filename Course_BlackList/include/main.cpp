#include "Account.h"
#include "Setup.hpp"

#include "UserConsoleInput.h"


#include <array>
#include <memory>

#include <map>

#include <unordered_map>

#include <queue>

#include "PrintFormat.h"

int CONSTANT::CONSOLE_WIDTH;
int CONSTANT::CELLS_MAX;
int CONSTANT::CELL_WIDTH;
int CONSTANT::ROW_WIDTH;
int CONSTANT::BOX_WIDTH;

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Setup();
	CONSTANT::CONSOLE_WIDTH = Console().WindowSize().X;
	CONSTANT::ROW_WIDTH = CONSTANT::CONSOLE_WIDTH * 0.8;
	CONSTANT::BOX_WIDTH = CONSTANT::CONSOLE_WIDTH * 0.5;

	//std::cout << ConsoleFormat::StringBox("dsfsfsfs");


	std::map<int, int> map;

	std::vector<Account> vec;
	int size = 25;
	for (size_t i = 0; i < size; i++)
	{
		std::string login = std::to_string((i + 1) * 123);
		Password p = make_password(std::to_string(i));
		Account acc(login, std::to_string(rand() % 1000), p, Account::Access::Approved, Account::Level::Admin);
		acc.level = Account::Level::Client;
		vec.push_back(acc);
	}
	vec[0].access = vec[2].access = vec[4].access = vec[6].access = vec[9].access = Account::Access::Denied;
	vec[1].access = vec[3].access = Account::Access::Pendig;

	vec[0].level = Account::Level::Super;
	vec[4].level = Account::Level::Admin;
	vec[9].level = Account::Level::Admin;

	vec[9].setLogin("1321321312371eourhasfhlkdsflsjdfkldsjflksjdflsdjflksdfjsdfksdflksjdflksjdfsidu7f980u3209u4oi32jhl");



	int page = 2;
	int pos = page * 10;
	int max_page = vec.size() / 10;
	manip::pos initial_pos;
	while (true)
	{
		std::cout << Account::TopRow();
		size_t max_i = ((vec.size() - page * 10) >= 10) ? (page + 1) * 10 : (page + 1) * 10 - (10 - vec.size() % 10);
		max_i -= 1;
		for (size_t i = page * 10; i <= max_i; i++)
		{

			if (i == pos)
			{
				std::cout << vec[i].InfoRow_highlight(i + 1);
			}
			else

				std::cout << vec[i].InfoRow(i + 1);
		}

		char ch = _getch();
		bool active = true;

		if (ch == CONSTANT::KEY_ARROW)
		{
			ch = _getch();
			if (ch == CONSTANT::KEY_ARROW_DOWN)
			{
				if (pos < max_i)
					pos++;
			}
			else if (ch == CONSTANT::KEY_ARROW_UP)
			{
				if (pos > page * 10)
					pos--;
			}
			else if (ch == CONSTANT::KEY_ARROW_LEFT)
			{
				if (page > 0)
				{
					page--;
					pos = 10 * page;
					ClearScreen();
				}
			}
			else if (ch == CONSTANT::KEY_ARROW_RIGHT)
			{
				if (page < max_page)
				{
					page++;
					pos = 10 * page;
					ClearScreen();

				}
			}

		}
		else if (ch == CONSTANT::ENTER)
		{

			ClearScreen();
			int line = 0;
			while (true)
			{
				for (int i = 0; i < 20; i++)
				{
					std::string color = manip::bg_cyan;
					if (i == line)
						color = manip::bg_cyan_bright;
					ConsoleFormat::PrintCenteredNewLine("Это ты типо нажал ЕНТЕР и теперь должен быть переход к меню с функциями для выбранной ячейки, но пока ничего не готово. Нажми теперь ЕСКЕЙП " + std::to_string(i),
						color, ':');
				}

				ch = _getch();
				if (ch == CONSTANT::KEY_ARROW)
				{
					ch = _getch();
					if (ch == CONSTANT::KEY_ARROW_DOWN)
					{
						if (line < 20 - 1)
							line++;
					}
					else if (ch == CONSTANT::KEY_ARROW_UP)
					{
						if (line > 0)
							line--;
					}
				}
				else if (ch == CONSTANT::ENTER)
					break;
				std::cout << manip::pos(0, 0);


			}
			ClearScreen();
			initial_pos = { 0,0 };
		}

		std::cout << manip::pos(initial_pos);
	}

}
