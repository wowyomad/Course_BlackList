#include "UserConsoleInput.h"
#include "Date.h"
#include "PrintFormat.h"
#include "common.h"

#include <conio.h>
#include <regex>
#include <sstream>
#include <iomanip>

bool is_russian(const char ch)
{
	return ch >= 'а' and ch <= 'я' or ch >= 'А' and ch <= 'Я';
}

bool is_english(const char ch)
{
	return ch >= 'a' and ch <= 'z' or ch >= 'A' and ch <= 'Z';
}

std::string InputPassword(unsigned min, unsigned max)
{

	if (min > max)
		std::swap(min, max);

	std::string password;

	unsigned char ch = 0;

	bool failed = true;

	do
	{
		if (failed)
		{
			std::cout << "Пароль: ";
			failed = false;
		}

		ch = _getch();
		if (ch == CONSTANT::ENTER)
		{
			if (password.length() < min or password.length() > max)
			{
				std::cout << "\nОшибка. Минимальная длина " << min << " , максимальная " << max << ".\n";
				password.clear();
				failed = true;
			}
			else break;

		}
		else if (ch == CONSTANT::BACKSPACE)
		{
			if (password.length() > 0)
			{
				std::cout << "\b \b";
				password.pop_back();
			}
		}
		else if (ch == CONSTANT::KEY_ARROW)
			ch = _getch();
		else if (is_russian(ch))
		{
			/*std::cout << "\nОшибка. Введен русский символ!\n\n";
			password.clear();
			failed = true;*/
		}
		else
		{
			std::cout << '*';
			password.push_back(ch);
		}
	} while (true);
	std::cout << "\n\n";
	return password;
}

std::string InputLogin(unsigned min, unsigned max)
{
	std::string login;
	std::cout << "Логин может содеражать символы английского алфавита, цифры и нижнее подчервкивание.\n";
	unsigned char ch = 0;
	bool failed = true;
	do
	{
		if (failed)
		{
			std::cout << "Логин: ";
			failed = false;
		}
		ch = _getch();
		if (ch == CONSTANT::ENTER)
		{
			if (login.length() == 0)
				continue;

			if (login.length() < min)
			{
				std::cout << "\nОшибка. Логин слишком короткий\n\n";
				login.clear();
				failed = true;
			}
			else if (login.length() > max)
			{
				std::cout << "\nОшибка. Логин слишком длинный\n\n";
				failed = true;
				login.clear();
			}
			else break;
		}
		else if (ch == '\b')
		{
			if (login.length() > 0)
			{
				std::cout << "\b \b";
				login.pop_back();
			}
		}
		else if (ch == ' ')
		{
			continue;
		}
		else if (ch == CONSTANT::KEY_ARROW)
			ch = _getch();
		else if (is_english(ch) || isdigit(ch) || ch == '_')
		{
			std::cout << ch;
			login.push_back(ch);
		}
		/*else
		{
			std::cout << "\nНедопустимый символ\n\n";
			failed = true;
			login.clear();
		}*/
	} while (true);
	std::cout << "\n\n";
	return login;
}

std::string InputString(const char* msg)
{
	std::string string = "";
	if (msg) std::cout << msg;
	while (string.empty())
		std::getline(std::cin, string);
	return string;
}

tm InputDate(char* msg)
{
	tm date;

	std::cout << msg << "\n";
	time_t rawtime = std::time(NULL);
	tm currentTime;
	localtime_s(&currentTime, &rawtime);
	int minMonth = 1;
	int minDay = 1;
	int maxDay = 0;

	InputVar(date.tm_year, currentTime.tm_year + 1900, currentTime.tm_year + 1900 + 10, "Год: ");
	date.tm_year -= 1900;
	if (date.tm_year == currentTime.tm_year)
		minMonth = currentTime.tm_mon + 1;

	InputVar(date.tm_mon, minMonth, 12, "Месяц: ");
	if (date.tm_year == currentTime.tm_year)
		if (date.tm_mon == currentTime.tm_mon)
			minDay = currentTime.tm_mday;
	date.tm_mon--;

	int year = date.tm_year + 1900;
	switch (date.tm_mon)
	{
		//февраль
	case 1:
		if (year % 400 == 0)
			maxDay = 29;
		else if (year % 100 == 0)
			maxDay = 28;
		else if (year % 4 == 0)
			maxDay = 29;
		else
			maxDay = 28;
		break;
		//апрель, июнь, сент¤брь, но¤брь
	case 3: case 5: case 8: case 10:
		maxDay = 30;
		break;
		//остальные мес¤цы
	default:
		maxDay = 31;
		break;
	}

	InputVar(date.tm_mday, minDay, maxDay, "Число: ");
	return date;
}

tm InputDate(manip::pos home)
{
	const char regex_pattern[] = "\\b\\d{2}(.)\\d{2}(.)\\d{4}\\b";
	const char date_pattern[] = "%d.%m.%Y";

	const unsigned short index[8] = { 0,1, 3,4, 6,7,8,9 };
	unsigned short y = home.y;
	unsigned short x = home.x;

	while (true)
	{
		std::string date = "__.__.____";
		unsigned i = 0;
		tm tm;
		while (true)
		{
			std::cout << manip::pos(x, y) << date << manip::pos(x + index[i], y);
			char ch[2]{ _getch(), '\0' };
			if (std::regex_match(ch, std::regex("[0-9]")))
			{
				if (i < 8)
				{
					std::cout << *ch;
					date[index[i]] = *ch;
					i++;
				}
			}
			else if (*ch == '\b')
			{
				if (i > 0)
				{
					date[index[i - 1]] = '_';
					i--;
				}
			}
			else
			{
				if (std::regex_match(date, std::regex(regex_pattern)))
					break;
			}
		}
		if (str_to_tm_leaps(date.c_str(), date_pattern, &tm))
		{
			std::cout << '\n';
			return tm;
		}
	}
}


tm InputTime(manip::pos begin)
{
	return tm();
}

std::string DateString(tm& date)
{
	std::stringstream date_stream;
	date_stream << std::put_time(&date, "%d.%m.%Y");
	return date_stream.str();

}

std::string TimeString(tm& time)
{
	return std::string();
	std::stringstream time_stream;
	time_stream << std::put_time(&time, "%H:%M:%S");
	return time_stream.str();
}

bool AcceptAction(std::string& msg)
{
	using namespace ConsoleFormat;

	PrintCenteredNewLine(msg, manip::reset);

	PrintCenteredLine(MSG_ACCEPT, manip::bg_green_bright);
	PrintCenteredLine(MSG_DECLINE, manip::bg_red_bright);

	char input;
	do
	{
		input = _getch();

	} while (input != CONSTANT::ENTER and input != CONSTANT::ESCAPE);

	switch (input)
	{
	case CONSTANT::ENTER:
		return true;
	case CONSTANT::ESCAPE:
		return false;
	}
}

bool AcceptAction(std::string&& msg)
{
	return AcceptAction(msg);
}

bool AcceptAction(const char* msg)
{
	return AcceptAction(std::string(msg));
}
