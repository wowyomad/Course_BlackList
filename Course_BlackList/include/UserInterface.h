#pragma once
#include "PrintFormat.h"	

#include "Deposit.h"

namespace message
{
	using message = const char[];

	static message hello = "Добро пожаловать в ад";
	
}

namespace UI
{
	void Menu_Main();

	void Login();
	void Register();

	void PrintHeader(const char* name);
	void PrintOption(const char* option);
	void PrintOption_highlight(const char* option);

	void WaitTillEnter();
}