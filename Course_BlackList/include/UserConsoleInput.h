#pragma once

#include <string>
#include <iostream>
#include <conio.h>

#include "common.h"
#include "console_manip.h"

const char MSG_ACCEPT[] = "ENTER - Подтверить";
const char MSG_DECLINE[] = "ESC - Отменить";

bool is_russian(const char ch);
bool is_english(const char ch);

std::string InputPassword(unsigned min, unsigned max);
std::string InputLogin(unsigned min, unsigned max);
std::string InputString(unsigned min, unsigned max, char* msg);
tm InputDate(char* msg);
tm InputDate(manip::pos begin = manip::pos(0,0));
tm InputTime(char* msg);
std::string DateString(tm& date);
std::string TimeString(tm& time);

bool AcceptAction(std::string& msg);
bool AcceptAction(const char* msg);
bool AcceptAction(std::string&& msg);

template <typename _Type>
void InputVar(_Type& var, unsigned min, unsigned max, const char msg[] = "Ввод: ")
{
	while (true)
	{
		std::cout << msg;
		std::cin >> var;
		if (!(std::cin))
		{
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Неверный ввод!\n\n";
		}
		else if (var < min || var > max)
		{
			std::cout << "\nМинимум: " << min << "\nМаксимум: " << max << "\n\n";
		}
		else break;
	}
}