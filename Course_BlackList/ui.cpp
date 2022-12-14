#include "ui.h"

#include <conio.h>
#include <iomanip>
#include <memory>

#include "Account.h"
#include "UserConsoleInput.h"
#include "TableInterface.hpp"
#include "PrintFormat.h"
#include "messages.h"

class Account;
class Client;



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
	Deposit::ReadFile();
	Client::ReadFile();

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
		UIW::Register(Level::Super);
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
				UIW::Register(Level::Client);
				break;
			}
		}

		else if (o.event() == events::back)
			break;

	} while (true);

	Account::WriteFile();
	Deposit::WriteFile();
	Client::WriteFile();
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
		case Level::Super:
			Main = Main_Super;
			break;
		case Level::Admin:
			Main = Main_Admin;
			break;
		case Level::Client:
			Main = Main_Client;
			break;
		default:
			throw std::exception();
		}
		UI::WaitTillEnter();
		this_login = account.get_login();
		Main(std::make_shared<Account>(account));
	}
	ClearScreen();
}

void UIW::Register(const Level level)
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

	std::vector<std::string> options{ "??????? ?????????", "??????? ?????????" };
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
				UIW::DepositTable_Admin(account_ptr);
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
void UIW::Main_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	std::string header = message::_Admin_header;

	std::vector<std::string> options{ "??????? ?????????", "??????? ?????????" };
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
				UIW::DepositTable_Admin(account_ptr);
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
	std::string header = message::_Client_header;

	std::vector<std::string> options{ "??? ????????", "????????? ????????" };

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
				UIW::ClientDeposits_Client(account_ptr);
				break;
			case 1:
				UIW::ClientOptions_Client(account_ptr);
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

void UIW::UserTable_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	const COORD home = { 0, 0 };
	const size_t rows = 10;
	std::string header = "?????? ?????????";


	TableInterface<Account> ti(Account::vector_ref(), header, home, rows);

	while (true)
	{
		ti.render();
		ti.update();

		event event = ti.event();

		if (event == events::select)
		{
			ClientOptions_Admin(Account::get_account(ti.index()));
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
	UserTable_Admin(account_ptr);
}

void UIW::DepositTable_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	std::string header = "????????? ??????";
	const std::vector<std::shared_ptr<Deposit>>& deposits = Deposit::vector_ref();

	TableInterface<Deposit> ti(deposits, header, { 0, 0 }, 10);

	while (ti.event() != events::back)
	{
		ti.render();
		ti.update();

		if (ti.event() == events::other)
		{
			UIW::NewDeposit_Admin(account_ptr);
			ti.refresh();
		}
	}

	ClearScreen();
}

void UIW::DepositTable_Client(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	std::string header = "????????? ??????";
	auto deposits = Deposit::vector_ref();

	TableInterface<Deposit> ti(deposits, header, { 0, 0 }, 10);

	while (ti.event() != events::back)
	{
		ti.render();
		ti.update();

		if (ti.event() == events::select)
		{
			size_t index = ti.index();
			std::shared_ptr<Deposit> deposit = std::make_shared<Deposit>(Deposit::get_deposit(index));
			UIW::AddDeposit_Client(account_ptr, deposit);
			ti.refresh();
		}
	}

	ClearScreen();
}


void UIW::ClientDeposits_Client(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	std::string header = "??? ???????"; //message



	TableInterface<ClientDeposit> ti(account_ptr->GetClient()->deposit_ref(), header, { 0, 0 }, 10);

	while (ti.event() != events::back)
	{
		ti.render();
		ti.update();

		if (ti.event() == events::other)
		{
			UIW::DepositTable_Client(account_ptr);
			std::cout << account_ptr->GetClient()->deposits.size();
			ti.refresh();
		}
	}

	ClearScreen();
}

void UIW::ClientDeposits_Admin(std::shared_ptr<Account> account_ptr)
{
	ClientDeposits_Client(account_ptr);
}

void UIW::ClientOptions_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	std::string header = message::_Client_header;

	std::vector<std::string> options{ "??????", "????????? ????????" };

	OptionsInterface oi(options, header, { 0, 8 });

	while (oi.event() != events::back)
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
				UIW::ClientDeposits_Client(account_ptr);
				break;
			case 1:
				UIW::ClientOptions_Admin(account_ptr);
				break;
			}
		}
	}
	ClearScreen();
}

void UIW::ClientOptions_Client(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	std::string header = "????????? ????????";
	std::vector<std::string> opeions{ "???????? ?????", "???????? ??????" };

	OptionsInterface oi(opeions, header, { 0,8 });

	while (oi.event() != events::back)
	{
		oi.render();
		oi.update();

		if (oi.event() == events::select)
		{
			ClearScreen({ 0, 8 });
			switch (oi.position())
			{
			case 0:
				UIW::UpdateLogin_any(account_ptr);
				break;
			case 1:
				UIW::UpdatePassword_any(account_ptr);
				break;
			}
		}
	}
	ClearScreen();
}

void UIW::RemoveAcccount_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
}
void UIW::RemoveAccount_Super(std::shared_ptr<Account> account_ptr)
{
	UIW::RemoveAcccount_Admin(account_ptr);
}



void UIW::AddDeposit_Client(std::shared_ptr<Account> account_ptr, std::shared_ptr<Deposit> deposit)
{
	ClearScreen();

	std::string header = "???????? ?????? ??????";

	std::vector<std::string> available;
	for (size_t i = 30; i <= 360; i += 30)
	{
		available.push_back(std::to_string(i) + " ????");
	}

	OptionsInterface oi(available, header, { 0, 6 });
	while (oi.event() != events::select)
	{
		oi.render();
		oi.update();
	}

	unsigned days = (oi.position() + 1) * 30;

	Money min = deposit->deposit_min;
	Money max = deposit->deposit_max;

	Money invest;
	InputVar<Money>(invest, min, max, "?????: ");
	tm current_time = TimeDate::current_time_tm();
	TimeDate date_now(&current_time);
	ClientDeposit new_deposit = make_client_deposit(deposit->title, invest, deposit->int_rate, date_now, days);



	ClearScreen();
	new_deposit.print_topRow_index();
	new_deposit.print_row_index(0);
	UI::PrintMessage("??????????? ??????????");
	if (UI::UserAccept())
	{
		account_ptr->GetClient()->add_deposit(new_deposit);
		UI::PrintMessage("????? ??? ??????? ??????");
	}
	else
		UI::PrintMessage("????? ??? ???????");

	ClearScreen();
}
void UIW::NewDeposit_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();

	UI::PrintHeader("?????????? ?????? ??????");
	std::cout << manip::pos(0, 6);

	std::string title = InputString("???????? ??????: ");
	Money min, max;
	InputVar(min, 0ll, 100'000'000'000, "??????????? ?????: ");
	InputVar(max, min , 100'000'000'000'000, "???????????? ?????: ");
	float int_rate;
	InputVar(int_rate, 0.1f, 100.0f, "?????????? ??????, %: ");
	int_rate /= 100;
	Deposit new_deposit = make_deposit(title, int_rate, min, max);

	new_deposit.print_TopRow_index();
	new_deposit.print_row_index(0);
	UI::PrintMessage("??????????? ??????????");
	if (UI::UserAccept())
	{
		Deposit::vector_push(new_deposit);
		UI::PrintMessage("????? ??? ??????? ??????");
	}
	else
		UI::PrintMessage("????? ??? ???????");

	ClearScreen();
}


void UIW::UpdatePassword_any(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
}
void UIW::UpdateLogin_any(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
}