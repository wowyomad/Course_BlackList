#pragma once

#include <string>
#include <iostream>
#include <conio.h>

#include "common.h"

bool is_russian(const char ch);
bool is_english(const char ch);

std::string InputPassword(unsigned min, unsigned max);
std::string InputLogin(unsigned min, unsigned max);
std::string InputString(unsigned min, unsigned max, char* msg);
tm InputDate(char* msg);
tm InputTime(char* msg);
std::string DateString(tm& date);
std::string TimeSTring(tm& time);
bool AcceptAction(char* msg);

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