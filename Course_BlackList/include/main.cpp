#include "common.h"
#include <Windows.h>
#include "Setup.hpp"
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

	
	Deposit deposit;
	deposit = make_deposit("Дешевка", 0.125, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Булочка", 0.13, 1000, 5000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Привет", 0.14, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Как дела?", 0.11, 5000, 12500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Нормально", 0.25, 250, 2500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Нормально - нереально", 0.15, 1500, 50000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Реально - нереально", 0.15, 100, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("У лукоморья дуб зеленый", 0.1, 1000, (Money)400000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Златая цепь на дубе том", 0.1253, 1000, 50000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("И днём, и ночью кот учёный всё ходит по цепи кругом", 0.125, 1000, 400000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Вот и помер кот", 0.125, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Гейб - король", 0.125, 100, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Тупо топ", 0.145, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("А почему нет?", 0.125, 100, 50000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("О, вижу их!", 0.125, 1000, 400000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Крысичи", 0.125, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Hollow Knight: Silksong", 0.125, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Философия Ахилеса", 0.125, 1000, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Джава лучше плюсов", 0.125, 1000, 50000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Амд лучше интел", 0.24, 100, 3500);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Болт, который был положен на курсовую", 0.99, 1000, 400000);
	Deposit::vector_push(deposit);
	deposit = make_deposit("Дотеры - нелюди", 0.125, 100, 50000);
	Deposit::vector_push(deposit);

	Account acc;
	acc = make_account("boba", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("aboba", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("alexei", "123", Account::Access::Denied, Level::Client);
	Account::vector_push(acc);
	acc = make_account("geimer", "123", Account::Access::Denied, Level::Client);
	Account::vector_push(acc);
	acc = make_account("poompa", "123", Account::Access::Approved, Level::Admin);
	Account::vector_push(acc);
	acc = make_account("fuck_you", "123", Account::Access::Pendig, Level::Client);
	Account::vector_push(acc);
	acc = make_account("fsdfsdf", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("123", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("motherfucker", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("antonio", "123", Account::Access::Approved, Level::Admin);
	Account::vector_push(acc);
	acc = make_account("uwu", "123", Account::Access::Denied, Level::Client);
	Account::vector_push(acc);
	acc = make_account("gamer", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("jenshina", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	acc = make_account("slave", "123", Account::Access::Approved, Level::Client);
	Account::vector_push(acc);
	Account::WriteFile();
	Client::WriteFile();
	Deposit::WriteFile();

	UIW::MainScreen();

}
