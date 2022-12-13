#include "Account.h"
#include "Setup.hpp"

#include "UserConsoleInput.h"
#include "Date.h"

#include "Deposit.h"

#include <array>
#include <memory>

#include <map>

#include <unordered_map>

#include <queue>

#include "PrintFormat.h"

int CONSTANT::CONSOLE_WIDTH;
int CONSTANT::CONSOLE_HEIGHT;
int CONSTANT::CELLS_MAX;
int CONSTANT::CELL_WIDTH;
int CONSTANT::ROW_WIDTH;
int CONSTANT::BOX_WIDTH;

#include "UserInterface.h"

void demo_main()
{
	COORD home{ 0, 7 };
	manip::pos initial_pos(home);
	std::cout << initial_pos;
	/*for (size_t i = 0; i < 14; i++)
	{
		std::cout << "row\n";
	}*/

	std::vector<Account> vec;
	int size = 36;
	for (size_t i = 0; i < size; i++)
	{
		std::string login = std::to_string((i + 1) * 123);
		Password p = make_password(std::to_string(i));
		Account acc(login, std::to_string(rand() % 1500), p, Account::Access::Approved, Account::Level::Admin);
		acc.level = Account::Level::Client;
		vec.push_back(acc);
	}
	vec[0].access = vec[2].access = vec[4].access = vec[6].access = vec[9].access = Account::Access::Denied;
	vec[1].access = vec[3].access = Account::Access::Pendig;

	vec[0].level = Account::Level::Super;
	vec[4].level = Account::Level::Admin;
	vec[9].level = Account::Level::Admin;

	vec[9].setLogin("1321321312371eourhasfhlkdsflsjdfkldsjflksjdflsdjflksdfjsdfksdflksjdflksjdfsidu7f980u3209u4oi32jhl");
	vec[2].setLogin("fsdfdsf123215r132e12edsdadfsdfdsfds32432532asd");

	vec[5].setLogin("dsfdsfsf2131232134123");



	int cols = 10;
	int page = 2;
	int pos = page * cols;
	int max_page = (vec.size() - 1) / cols;
	while (true)
	{
		std::cout << Account::TopRow_num();
		size_t max_i = ((vec.size() - page * cols) >= cols) ? (page + 1) * cols : (page + 1) * cols - (cols - vec.size() % cols);
		max_i -= 1;
		for (size_t i = page * cols; i <= max_i; i++)
		{

			if (i == pos)
			{
				std::cout << vec[i].InfoRow_highlight(i + 1);
			}
			else

				std::cout << vec[i].InfoRow(i + 1);
		}
		std::cout << manip::pos(home);

		char ch = _getch();
		bool active = true;

		if (ch == CONSTANT::KEY_ARROW)
		{
			ch = _getch();
			if (ch == CONSTANT::KEY_ARROW_DOWN)
			{
				if (pos < max_i)
					pos++;
				else if (page < max_page)
				{
					page++;
					pos++;
					ClearScreen(home);
				}
			}
			else if (ch == CONSTANT::KEY_ARROW_UP)
			{
				if (pos > page * cols)
					pos--;
				else if (page > 0)
				{
					page--;
					pos--;
					ClearScreen(home);
				}
			}
			else if (ch == CONSTANT::KEY_ARROW_LEFT)
			{
				if (page > 0)
				{
					page--;
					pos = cols * page;
					ClearScreen(home);
				}
			}
			else if (ch == CONSTANT::KEY_ARROW_RIGHT)
			{
				if (page < max_page)
				{
					page++;
					pos = cols * page;
					ClearScreen(home);

				}
			}
		}
		else if (ch == CONSTANT::ENTER)
		{

			ClearScreen(home);
			int line = 0;
			while (true)
			{
				for (int i = 0; i < 20; i++)
				{
					std::string color = manip::cyan;
					if (i == line)
						color = manip::bg_cyan_bright;
					ConsoleFormat::PrintCenteredNewLine("Здесь ничего не работает. Стрлочками можно перемещатьс вверх-вниз, а ENTER вернет тебя назад" + std::to_string(i),
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
				std::cout << manip::pos(home);


			}
			ClearScreen(home);
		}
		else if (ch == CONSTANT::ESCAPE)
		{
			ClearScreen();
			return;
		}

		std::cout << manip::pos(home);
	}
}

#include <set>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Setup();
	CONSTANT::CONSOLE_WIDTH = Console().WindowSize().X;
	CONSTANT::CONSOLE_HEIGHT = Console().WindowSize().Y;
	CONSTANT::ROW_WIDTH = CONSTANT::CONSOLE_WIDTH * .8;
	CONSTANT::BOX_WIDTH = CONSTANT::CONSOLE_WIDTH * 0.5;


	COORD home = { 0, 20 };

	std::vector<std::string> options{ "option1", "option2", "opion3", "opion4" };
	OptionsInterface o(options, "demo main", home);

	ClearScreen();

	std::vector<Account> vec;
	int size = 36;
	for (size_t i = 0; i < size; i++)
	{
		std::string login = std::to_string((i + 1) * 123);
		Password p = make_password(std::to_string(i));
		Account acc(login, std::to_string(rand() % 1500), p, Account::Access::Approved, Account::Level::Admin);
		acc.level = Account::Level::Client;
		vec.push_back(acc);
	}
	vec[0].access = vec[2].access = vec[4].access = vec[6].access = vec[9].access = Account::Access::Denied;
	vec[1].access = vec[3].access = Account::Access::Pendig;

	vec[0].level = Account::Level::Super;
	vec[4].level = Account::Level::Admin;
	vec[9].level = Account::Level::Admin;

	vec[9].setLogin("1321321312371eourhasfhlkdsflsjdfkldsjflksjdflsdjflksdfjsdfksdflksjdflksjdfsidu7f980u3209u4oi32jhl");
	vec[2].setLogin("fsdfdsf123215r132e12edsdadfsdfdsfds32432532asd");

	vec[5].setLogin("dsfdsfsf2131232134123");

	for (auto& it : vec)
		Account::vector_push(it);

	size_t rows = 10;
	COORD start_coords = { 0, 4 };
	TI_accounts ti(Account::vector_ref(), rows, start_coords);

	while (true)
	{
		ti.render();
		ti.update();

		event event = ti.event();

		if (event == events::select)
		{
			ClearScreen();
			std::cout << manip::pos(0, 10);
			size_t pos = ti.index();
			std::cout << Account::TopRow();
			std::cout << Account::vector_get(pos)->InfoRow();

			UI::WaitTillEnter();
			ClearScreen();
		}
		else if (event == events::back)
		{
			ClearScreen();
			UI::PrintMessage("Пока");
			break;
		}
	}
	exit(1);

	while (true)
	{
		o.render();
		o.update();

		event event = o.event();

		if (event == events::select)
		{
			ClearScreen();

			switch (o.position())
			{
			case 0:
				demo_main();
				break;
			case 1:
				UI::MainScreen();
				break;
			case 2:
				UI::PrintMessage("Опция пять");
				UI::WaitTillEnter();
				break;
			case 3:
				UI::PrintMessage("Опция четыре");
				UI::WaitTillEnter();
				break;
			}
			std::cout << manip::pos(0, 16);
			ClearScreen();

		}
		else if (event == events::back)
		{
			ClearScreen();
			break;
		}
	}
}
