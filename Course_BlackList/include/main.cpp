#include "common.h"
#include <Windows.h>
#include "Setup.hpp"

#include "Account.h"

#include "../ui.h"


int CONSTANT::CONSOLE_WIDTH;
int CONSTANT::CONSOLE_HEIGHT;
int CONSTANT::CELLS_MAX;
int CONSTANT::CELL_WIDTH;
int CONSTANT::ROW_WIDTH;
int CONSTANT::BOX_WIDTH;


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
	
	Account acc = make_account("123", "123", Account::Access::Approved, Level::Admin);
	Client cli = make_from_account(std::make_shared<Account>(acc));

	Client::vector_push(cli);
	Account::vector_push(acc);


	UIW::MainScreen();

}
