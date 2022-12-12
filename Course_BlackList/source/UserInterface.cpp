#include "UserInterface.h"

#include <conio.h>
#include <iomanip>

void UI::HelloScreen()
{
	bool done = false;

	while (!done)
	{
		ClearScreen();

		PrintHeader(message::_HelloScreen_header);

		PrintOption("1." + message::_HelloScreen_login);
		PrintOption("2." + message::_HelloScreen_login);

		UI::WaitTillEnter();
	}
}

void UI::Login()
{

}

void UI::Register()
{

}

void UI::PrintHeader(const message::message& name)
{
	ConsoleFormat::PrintCenteredLine("", "", '*');
	ConsoleFormat::PrintCenteredLine(name, "", '~');
	ConsoleFormat::PrintCenteredLine("", "", '*');
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

void UI::WaitTillEnter()
{
	ConsoleFormat::PrintCenteredNewLine("Нажмите ENTER, чтобы продолжить", manip::bg_green_bright, ':');
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
		last_event = events::select;
		break;
	
	case CONSTANT::ESCAPE:
		last_event = events::back;
		break;
	}
}

void OptionsInterface::render()
{
	unsigned short i = 0;
	std::cout << manip::pos(home);
	for (const std::string& option : options)
	{
		if (i == pos)
			UI::PrintOption_highlight(option);
		else
			UI::PrintOption(option);
		i++;
	}
}

OptionsInterface::OptionsInterface(const std::vector<std::string>& options, COORD home)
	: options(options), pos(0), max_pos(options.size() - 1), last_event(events::none)
{
	this->home = Console::GetCursourPosition();

	this->home = home;
}

void OptionsInterface::move_up()
{
	if (pos > 0)
		pos--;
}

void OptionsInterface::move_down()
{
	if (pos < max_pos)
		pos++;
}

event OptionsInterface::event() const
{
	return last_event;
}

unsigned short OptionsInterface::position() const
{
	return pos;
}