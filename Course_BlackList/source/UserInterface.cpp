#include "UserInterface.h"

#include <conio.h>
#include <iomanip>
#include <memory>

#include "Account.h"
#include "UserConsoleInput.h"
#include "TableInterface.hpp"

#include "messages.h"


void UIW::HelloScreen()
{
	ClearScreen();

	UI::PrintHeader(message::_HelloScreen_header);

	UI::WaitTillEnter();

	UIW::MainScreen();
}

void UIW::MainScreen()
{
	Account::ReadFile();

	std::vector<std::string>options{
		message::_MainScreen_login,
		message::_MainScreen_register
	};

	COORD home = { 0, 4 };
	OptionsInterface o(options, message::_MainScreen_header, home);

	//Account::ReadFile();

	while (!Account::super_user_present())
	{
		UI::PrintMessage(message::_MainScreen_no_super_user);
		UI::PrintMessage(message::_MainScreen_register_as_super);
		UI::WaitTillEnter();
		UIW::Register(Account::Level::Super);
	}


	do
	{
		o.render();
		o.update();

		if (o.event() == events::select)
		{
			switch (o.position())
			{
			case 0:
				UIW::Login();
				break;
			case 1:
				UIW::Register(Account::Level::Client);
				break;
			}
		}

		else if (o.event() == events::back)
			break;

	} while (true);

	Account::WriteFile();
}

void UIW::Login()
{
	bool done = false;
	bool logged = false;

	Account account;

	do
	{
		ClearScreen();
		UI::PrintHeader(message::_Login_header);

		std::string login = InputLogin(CONSTANT::LOGIN_LEN_MIN, CONSTANT::LOGIN_LEN_MAX);
		std::string password = InputPassword(CONSTANT::PASSWORD_LEN_MIN, CONSTANT::PASSWORD_LEN_MAX);

		try
		{
			account = *Account::get_account(login);
			if (account.get_password().same_as(password))
				if (account.access != Account::Access::Denied)
				{
					done = true;
					logged = true;
				}
				else
				{
					UI::PrintMessage(message::_Login_unavailable);
				}
			else
			{
				UI::PrintMessage(message::_Login_fail);

			}
		}
		catch (std::out_of_range& exc)
		{
			UI::PrintMessage(message::_Login_fail);
		}

		if (!done)
		{
			UI::PrintMessage(message::_Login_back);
			if (!UI::UserAccept()) done = true;
		}
	} while (!done);

	if (logged)
	{
		UI::PrintMessage(message::_Login_success);
		void (*Main)(std::shared_ptr<Account>);


		switch (account.level)
		{
		case Account::Level::Super:
			Main = Main_Super;
			break;
		case Account::Level::Admin:
			Main = Main_Admin;
			break;
		case Account::Level::Client:
			Main = Main_Client;
			break;
		default:
			throw std::exception();
		}
		UI::WaitTillEnter();
		Main(std::make_shared<Account>(account));
	}
	ClearScreen();
}

void UIW::Register(const Account::Level level)
{

	bool done = false;
	bool registered = false;

	do
	{
		ClearScreen();

		UI::PrintHeader(message::_Register_header);

		std::string login = InputLogin(CONSTANT::LOGIN_LEN_MIN, CONSTANT::LOGIN_LEN_MAX);
		std::string password = InputPassword(CONSTANT::PASSWORD_LEN_MIN, CONSTANT::PASSWORD_LEN_MAX);

		if (Account::login_is_uniqiue(login))
		{
			UI::PrintMessage(message::_Register_available);
			UI::PrintMessage(message::_Register_confirm);
			if (UI::UserAccept())
			{
				Account::Access access = Account::Access::Approved;


				Account new_account = make_account(login, password, access, level);
				Account::vector_push(new_account);
				done = true;
				registered = true;

				UI::PrintMessage(message::_Register_success);
			}
			else
			{
				UI::PrintMessage(message::_Register_fail);
				UI::PrintMessage(message::_Register_back);
				if (!UI::UserAccept()) done = true;
			}

		}
		else
		{
			UI::PrintMessage(message::_Register_unavailable);
			UI::PrintMessage(message::_Register_back);
			if (!UI::UserAccept()) done = true;
		}

	} while (!done);
	ClearScreen();

}


void UIW::Main_Super(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	std::string header = message::_Super_header;

	std::vector<std::string> options{ "Таблица аккаунтов", "Таблица депозитов" };
	OptionsInterface oi(options, header, { 0, 8 });

	while (true)
	{
		oi.render();
		oi.update();

		event event = oi.event();

		if (event == events::select)
		{
			switch (oi.position())
			{
			case 0:
				UIW::UserTable_Admin(account_ptr);
				break;
			case 1:
				UI::PrintMessage("Это еще не работает");
				break;
			}
		}
		else if (event == events::back)
		{
			break;
		}
	}

	UI::WaitTillEnter();
}
void UIW::Main_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	std::string header = message::_Admin_header;

	std::vector<std::string> options{ "Таблица аккаунтов", "Таблица депозитов" };
	OptionsInterface oi(options, header, { 0, 8 });

	while (true)
	{
		oi.render();
		oi.update();

		event event = oi.event();

		if (event == events::select)
		{
			ClearScreen({ 0, 8 });
			switch (oi.position())
			{
			case 0:
				UIW::UserTable_Admin(account_ptr);
				break;
			case 1:
				UI::PrintMessage("Это еще не работает");
				break;
			}
		}
		else if (event == events::back)
		{
			break;
		}
	}
	ClearScreen();
}
void UIW::Main_Client(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	UI::PrintHeader(message::_Client_header);
	UI::WaitTillEnter();
}

void UIW::UserTable_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	const COORD home = { 0, 0 };
	const size_t rows = 10;
	std::string header = "Список аккаунтов";


	TableInterface<Account> ti(Account::vector_ref(), header, home, rows);

	while (true)
	{
		ti.render();
		ti.update();

		event event = ti.event();

		if (event == events::select)
		{

		}
		else if (event == events::back)
		{
			break;
		}
	}
	ClearScreen();
}

void UIW::UserTable_Super(std::shared_ptr<Account> account_ptr)
{
}
