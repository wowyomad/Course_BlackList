#pragma once


#include "Account.h"
#include <string>



namespace UIW
{
	static std::string this_login;

	void HelloScreen();

	void MainScreen();

	void Login();
	void Register(const Level level);

	void Main_Super(std::shared_ptr<Account> account_ptr);
	void Main_Admin(std::shared_ptr<Account> account_ptr);
	void Main_Client(std::shared_ptr<Account> account_ptr);


	void UserTable_Admin(std::shared_ptr<Account> account_ptr);
	void UserTable_Super(std::shared_ptr<Account> account_ptr);

	void DepositTable_Admin(std::shared_ptr<Account> account_ptr);
	void DepositTable_Client(std::shared_ptr<Account> account_ptr);


	void ClientDeposits_Client(std::shared_ptr<Account> account_ptr);
	void ClientDeposits_Admin(std::shared_ptr<Account> account_ptr);

	void ClientOptions_Admin(std::shared_ptr<Account> account_ptr);
	void ClientOptions_Client(std::shared_ptr<Account> account_ptr);

	void RemoveAcccount_Admin(std::shared_ptr<Account> account_ptr);
	void RemoveAccount_Super(std::shared_ptr<Account> account_ptr);

	void AddDeposit_Client(std::shared_ptr<Account> account_ptr, std::shared_ptr<Deposit> deposit);
	void NewDeposit_Admin(std::shared_ptr<Account> account_ptr);


	void UpdatePassword_any(std::shared_ptr<Account> account_ptr);
	void UpdateLogin_any(std::shared_ptr<Account> account_ptr);

}
