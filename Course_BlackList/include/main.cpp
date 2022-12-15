#include "Account.h"
#include "Setup.hpp"

#include "UserConsoleInput.h"
#include "Date.h"

#include "TableInterface.hpp"

#include "Deposit.h"

#include <memory>

#include "PrintFormat.h"


int CONSTANT::CONSOLE_WIDTH;
int CONSTANT::CONSOLE_HEIGHT;
int CONSTANT::CELLS_MAX;
int CONSTANT::CELL_WIDTH;
int CONSTANT::ROW_WIDTH;
int CONSTANT::BOX_WIDTH;

#include "UserInterface.h"

template <std::derived_from<Printable> _ItemType>
void foo(std::vector<std::shared_ptr<_ItemType>> items)
{
	TableInterface<_ItemType> ti(items, 10, { 0, 4 });
	while (true)
	{
		ti.render();
		ti.update();

		if (ti.event() == events::back)
			break;
	}
}

class B : public Printable
{
private:
	std::string name;
	float num;
	std::string random_num;
	static const unsigned format = !(
		ConsoleFormat::BORDER::LEFT |
		ConsoleFormat::BORDER::RIGHT |
		ConsoleFormat::BORDER::BOTTOM |
		ConsoleFormat::BORDER::VERTICAL);

public:
	B(const std::string& name, const float num)
		:name(name), num(num)
	{
		random_num = RNG::GenerateNum_str();
	}
public:
	virtual void print_row_index(const size_t& index) const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{
			name,
			std::to_string(num),
			random_num,
			std::to_string(index)
		};
		PrintRow(top_row, format);
	}
	virtual void print_row_index_highlight(const size_t& index) const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{
			name,
			std::to_string(num),
			random_num,
			std::to_string(index)
		};
		PrintRow_highlight(top_row, format);
	}
	virtual void print_row(const size_t& index) const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{
			name,
			std::to_string(num),
			random_num,
		};
		PrintRow(top_row, format);
	}
	virtual void print_row_highlight(const size_t& index) const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{
			name,
			std::to_string(num),
			random_num
		};
		PrintRow_highlight(top_row, format);
	}
	virtual void print_topRow_index() const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{ "Имя", "Число", "Случайное число", "Индекс" };
		PrintRow(top_row, BORDER::BOTTOM);
	}
};


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
	TableInterface<Account> ti(Account::vector_ref(), rows_count, start_coords);
	Account acc;
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
			acc.print_topRow_index();
			std::cout << Account::get_account(pos)->row_index(pos + 1);

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
}


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

	int length = 1000;
	std::vector<std::shared_ptr<B>> vector;
	for (size_t i = 0; i < length; i++)
	{
		B boba(std::to_string(i * 123), 1.0f / (rand() % 100 + 1));
		vector.push_back(std::make_shared<B>(boba));
	}

	foo<B>(vector);


	COORD home = { 0, 20 };

	std::vector<std::string> options{ "option1", "option2", "option3", "option4" };
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
