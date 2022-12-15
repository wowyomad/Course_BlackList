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

void demo_accounts()
{
	std::vector<Account> vec;
	int size = 1234;
	for (size_t i = 0; i < size; i++)
	{
		std::string login = std::to_string((i + 1) * 12345);
		Password p = make_password(std::to_string(i));
		Account acc(login, std::to_string(rand() % 32768 + 1), p, Account::Access::Approved, Account::Level::Admin);
		acc.level = Account::Level::Client;
		vec.push_back(acc);
	}
	for (auto& it : vec)
		Account::vector_push(it);

	size_t rows_count = 10;
	COORD start_coords = { 0, 4 };
	TI_accounts ti(Account::vector_ref(), rows_count, start_coords);

	while (true)
	{
		ti.render();
		ti.update();
		
		event event = ti.event();

		if (event == events::select)
		{
			std::cout << manip::pos(0, 10);
			size_t pos = ti.index();
			std::cout << Account::TopRow();
			std::cout << Account::vector_get(pos)->InfoRow();

			UI::WaitTillEnter();
		}
		else if (event == events::back)
		{
			ClearScreen();
			UI::PrintMessage("Пока");
			break;
		}
	}
}

#include <set>

//Чтобы консоль восприминала ANSI escape последовательность, нужно прописать в PowerShell команду: Set-ItemProperty HKCU:\Console VirtualTerminalLevel -Type DWORD 1
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

	while (true)
	{
		o.render();
		o.update();

		event event = o.event();

		if (event == events::select)
		{
			ClearScreen(home, CONSTANT::CONSOLE_HEIGHT);
			std::cout << manip::pos(home);
			switch (o.position())
			{
			case 0:
				demo_accounts();
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
