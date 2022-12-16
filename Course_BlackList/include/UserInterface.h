#pragma once
#include "PrintFormat.h"	
#include "Account.h"
#include "Deposit.h"
#include "TableInterface.hpp"

namespace UIW
{
	void HelloScreen();

	void MainScreen();

	void Login();
	void Register(const Account::Level level);

	void Main_Super(std::shared_ptr<Account> account_ptr);
	void Main_Admin(std::shared_ptr<Account> account_ptr);
	void Main_Client(std::shared_ptr<Account> account_ptr);


	void UserTable_Admin(std::shared_ptr<Account> account_ptr);
	void UserTable_Super(std::shared_ptr<Account> account_ptr);
}
