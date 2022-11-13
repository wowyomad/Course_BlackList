#include "../include/UserConsoleInput.h"

#include <conio.h>

bool is_russian(const wchar_t ch)
{
	return ch >= u'а' and ch <= u'я' or ch >= u'А' and ch <= u'Я';
}

bool is_english(const wchar_t ch)
{
	return ch >= u'a' and ch <= u'z' or ch >= u'A' and ch <= u'Z';
}

std::string InputPassword(unsigned min, unsigned max)
{

	if (min > max)
		std::swap(min, max);

	std::string password;

	wchar_t ch = 0;

	bool failed = true;

	do
	{
		if (failed)
		{
			std::cout << "Пароль: ";
			failed = false;
		}

		ch = _getwch();
		if (ch == ENTER)
		{
			if (password.length() < min or password.length() > max)
			{
				std::cout << "Ошибка. Минимальная длина " << min << " , максимальная " << max << ".\n";
				password.clear();
				failed = true;
			}
			else break;

		}
		else if (ch == BACKSPACE)
		{
			if (password.length() > 0)
			{
				std::cout << "\b \b";
				password.pop_back();
			}
		}
		else if (is_russian(ch))
		{
			std::cout << "\nОшибка. Введен русский символ!\n\n";
			password.clear();
			failed = true;
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
	wchar_t ch = 0;
	bool failed = true;
	do
	{
		if (failed)
		{
			std::cout << "Логин: ";
			failed = false;
		}
		ch = _getch();
		if (ch == ENTER)
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
				printf("\b \b");
				login.pop_back();
			}
		}
		else if (ch == ' ')
		{
			continue;
		}
		else if (is_english(ch) || isdigit(ch) || ch == '_')
		{
			printf("%c", ch);
			login.push_back(ch);
		}
		else
		{
			std::cout << "\nНедопустимый символ\n\n";
			failed = true;
			login.clear();
		}
	} while (true);
	std::cout << "\n\n";
	return login;
}

std::string InputString(unsigned min, unsigned max, char* msg)
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

tm InputTime(char* msg)
{
	return tm();
}

std::string DateString(tm& date)
{
	return std::string();
}

std::string TimeSTring(tm& time)
{
	return std::string();
}

bool AcceptAction(char* msg)
{
	return false;
}