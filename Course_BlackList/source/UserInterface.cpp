#include "UserInterface.h"

#include <conio.h>

void UI::Menu_Main()
{
	bool done = false;
}

void UI::Login()
{

}

void UI::Register()
{

}

void UI::PrintHeader(const char* name)
{
	ConsoleFormat::PrintCenteredLine("", "", '*');
	ConsoleFormat::PrintCenteredLine(name, "", '~');
	ConsoleFormat::PrintCenteredLine("", "", '*');
}

void UI::PrintOption(const char* option)
{
	ConsoleFormat::PrintCenteredNewLine(option, manip::cyan, ':');
}

void UI::PrintOption_highlight(const char* option)
{
	ConsoleFormat::PrintCenteredNewLine(option, manip::bg_cyan_bright, ':');
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

