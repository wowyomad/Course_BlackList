#include "UserInterface.h"

#include <conio.h>
#include <iomanip>
#include <memory>

#include "Account.h"
#include "UserConsoleInput.h"

void UI::HelloScreen()
{
	ClearScreen();

	PrintHeader(message::_HelloScreen_header);

	UI::WaitTillEnter();

	UI::MainScreen();
}

void UI::MainScreen()
{
	std::vector<std::string>options{
		message::_MainScreen_login,
		message::_MainScreen_register
	};

	COORD home = { 0, 4 };
	OptionsInterface o(options, message::_MainScreen_header, home);

	do
	{
		o.render();
		o.update();

		if (o.event() == events::select)
		{
			switch (o.position())
			{
			case 0:
				UI::Login();
				break;
			case 1:
				UI::Register(Account::Level::Client);
				break;
			}
		}

		else if (o.event() == events::back)
			break;

	} while (true);

	Account::WriteFile();
}

void UI::Login()
{
	bool done = false;
	bool logged = false;

	Account account;

	do
	{
		ClearScreen();
		PrintHeader(message::_Login_header);

		std::string login = InputLogin(CONSTANT::LOGIN_LEN_MIN, CONSTANT::LOGIN_LEN_MAX);
		std::string password = InputPassword(CONSTANT::PASSWORD_LEN_MIN, CONSTANT::PASSWORD_LEN_MAX);

		try
		{
			account = *Account::vector_get(login);
			if (account.getPassword().same_as(password))
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

void UI::Register(const Account::Level level)
{
	bool done = false;
	bool registered = false;

	do
	{
		ClearScreen();
		PrintHeader(message::_Register_header);

		std::string login = InputLogin(CONSTANT::LOGIN_LEN_MIN, CONSTANT::LOGIN_LEN_MAX);
		std::string password = InputPassword(CONSTANT::PASSWORD_LEN_MIN, CONSTANT::PASSWORD_LEN_MAX);

		if (Account::login_is_uniqiue(login))
		{
			PrintMessage(message::_Register_available);
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


void UI::Main_Super(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	UI::PrintHeader(message::_Super_header);
	UI::WaitTillEnter();
}
void UI::Main_Admin(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	UI::PrintHeader(message::_Admin_header);
	UI::WaitTillEnter();
}
void UI::Main_Client(std::shared_ptr<Account> account_ptr)
{
	ClearScreen();
	UI::PrintHeader(message::_Client_header);
	UI::WaitTillEnter();
}

bool UI::UserAccept()
{
	PrintAccept();
	PrintDecline();
	char input;
	do
	{
		input = _getch();
		switch (input)
		{
		case CONSTANT::ENTER:
			return true;
		case CONSTANT::ESCAPE:
			return false;
		}

	} while (true);
}


void UI::PrintAccept()
{
	ConsoleFormat::PrintCenteredLine(message::_accept, manip::green_bright);
}

void UI::PrintDecline()
{
	ConsoleFormat::PrintCenteredLine(message::_decline, manip::red_bright);
}

void UI::PrintHeader(const message::message& name)
{
	ConsoleFormat::PrintCenteredLine("", manip::purple_bright, ':');
	ConsoleFormat::PrintCenteredLine(name, manip::purple_bright, ':');
	ConsoleFormat::PrintCenteredLine("", manip::purple_bright, ':');
	UI::PrintLine();
}

void UI::PrintOption(const message::message& option)
{
	ConsoleFormat::PrintCenteredNewLine(option, manip::cyan, ':');
}

void UI::PrintMessage(const message::message& message)
{
	ConsoleFormat::PrintCenteredLine(message, "", ':');
}

void UI::PrintOption_highlight(const message::message& option)
{
	ConsoleFormat::PrintCenteredNewLine(option, manip::bg_cyan_bright, ':');
}

void UI::PrintLine(const char character)
{
	std::cout << std::setfill(character) << std::setw(CONSTANT::CONSOLE_WIDTH) << '\n';
}

void UI::PrintEnter()
{
	ConsoleFormat::PrintCenteredLine(message::_select, manip::green_bright);
}

void UI::PrintEsc()
{
	ConsoleFormat::PrintCenteredLine(message::_back, manip::red_bright);
}

void UI::WaitTillEnter()
{
	ConsoleFormat::PrintCenteredNewLine("Нажмите ENTER, чтобы продолжить", manip::green_bright, ':');
	char input;
	do
	{
		input = _getch();

	} while (input != CONSTANT::ENTER);
}

void OptionsInterface::update()
{
	char input;
	last_event = events::none;

	input = _getch();

	switch (input)
	{
	case CONSTANT::KEY_ARROW:
		input = _getch();
		switch (input)
		{
		case CONSTANT::KEY_ARROW_UP:
			move_up();
			break;
		case CONSTANT::KEY_ARROW_DOWN:
			move_down();
			break;
		}
		break;

	case CONSTANT::ENTER:
		to_update = true;
		last_event = events::select;
		break;

	case CONSTANT::ESCAPE:
		to_update = true;
		last_event = events::back;
		break;
	}
}

void OptionsInterface::render()
{
	unsigned short i = 0;
	if (to_update)
	{
		std::cout << manip::pos(0, 0);
		UI::PrintHeader(header);
		std::cout << manip::pos(home);
		for (const std::string& option : options)
		{
			if (i == pos)
				UI::PrintOption_highlight(option);
			else
				UI::PrintOption(option);
			i++;
		}
		UI::PrintEnter();
		UI::PrintEsc();
		to_update = false;
	}
}

OptionsInterface::OptionsInterface(const std::vector<std::string>& options, COORD home)
	: options(options), pos(0), max_pos(options.size() - 1), last_event(events::none),
	to_update(true)
{
	this->home = home;
}

OptionsInterface::OptionsInterface(const std::vector<std::string>& options, const std::string& header, COORD home)
	: options(options), pos(0), max_pos(options.size() - 1), last_event(events::none),
	to_update(true), header(header)
{
	this->home = home;
}

void OptionsInterface::move_up()
{
	if (pos > 0)
	{
		to_update = true;
		pos--;
	}
}

void OptionsInterface::move_down()
{
	if (pos < max_pos)
	{
		to_update = true;
		pos++;
	}
}

event OptionsInterface::event() const
{
	return last_event;
}

unsigned short OptionsInterface::position() const
{
	return pos;
}