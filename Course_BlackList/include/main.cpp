#include "Account.h"
#include "Setup.hpp"

#include "UserConsoleInput.h"
#include "Date.h"

#include "Deposit.h"

#include <memory>

#include "PrintFormat.h"


int CONSTANT::CONSOLE_WIDTH;
int CONSTANT::CONSOLE_HEIGHT;
int CONSTANT::CELLS_MAX;
int CONSTANT::CELL_WIDTH;
int CONSTANT::ROW_WIDTH;
int CONSTANT::BOX_WIDTH;

template <std::derived_from<Printable> _ItemType>
void foo(std::vector<std::shared_ptr<_ItemType>> items)
{
	TableInterface<_ItemType> ti(items, { 0, 0 }, 10);
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
	unsigned long num;
	std::string random_num;

public:
	B(const std::string& name, const unsigned num)
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
		PrintRow(top_row, BORDER::BOTTOM);
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
		PrintRow_highlight(top_row, BORDER::BOTTOM);
	}
	virtual void print_row(const size_t& index) const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{
			name,
			std::to_string(num),
			random_num,
		};
		PrintRow(top_row, BORDER::BOTTOM);
	}
	virtual void print_row_highlight(const size_t& index) const override
	{
		using namespace ConsoleFormat;
		std::vector<std::string> top_row{
			name,
			std::to_string(num),
			random_num
		};
		PrintRow_highlight(top_row, BORDER::BOTTOM);
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

	size_t rows_count = 10;
	COORD start_coords = { 0, 4 };
	TableInterface<Account> ti(Account::vector_ref(), start_coords, rows_count);

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


	UIW::MainScreen();
}
