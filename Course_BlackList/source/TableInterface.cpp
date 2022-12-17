#include "TableInterface.hpp"

#include <conio.h>
#include <iomanip>

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

	case CONSTANT::TAB:
		to_update = true;
		last_event = events::other;
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

void UI::PrintHeader(const message::msg& name)
{
	ConsoleFormat::PrintCenteredLine("", manip::purple_bright, ':');
	ConsoleFormat::PrintCenteredLine(name, manip::purple_bright, ':');
	ConsoleFormat::PrintCenteredLine("", manip::purple_bright, ':');
	PrintLine();
}

void UI::PrintOption(const message::msg& option)
{
	ConsoleFormat::PrintCenteredNewLine(option, manip::cyan, ':');
}

void UI::PrintMessage(const message::msg& message)
{
	ConsoleFormat::PrintCenteredLine(message, "", ':');
}

void UI::PrintString(const message::msg& message)
{
	ConsoleFormat::PrintCenteredLine(message, "");
}

void UI::PrintOption_highlight(const message::msg& option)
{
	ConsoleFormat::PrintCenteredNewLine(option, manip::bg_cyan_bright, ':');
}

void UI::PrintLine(const char character)
{
	std::cout << std::setfill(character) << std::setw(CONSTANT::CONSOLE_WIDTH) << '\n';
}


bool UI::UserAccept()
{
	UI::PrintAccept();
	UI::PrintDecline();
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
