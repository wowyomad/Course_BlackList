#pragma once

#include <string>

namespace common
{
	static const char msg_exception[] = "Неизвестное исключение.";
	static const char msg_invalid_separtor[] = "Ошибка получения десятичного разделителя.";

	//исключение: неизвестное
	class exception
	{
	protected:
		std::string message;
	public:
		exception(const std::string& info) { message = info; }
		exception() { message = msg_exception; }
		virtual const char* what() const { return message.c_str(); }
	};

	//исключение: десятичный разделитель
	class invalid_separtor : public exception
	{
	public:
		invalid_separtor(const std::string& info) : exception(info) {}
		invalid_separtor() : exception(msg_invalid_separtor) { };
	};
}

const char TAB = 9;
const char ENTER = 13;
const char BACKSPACE = 8;

const char KEY_ARROW = 224;
const char KEY_ARROW_UP = 72;
const char KEY_ARROW_DOWN = 80;
const char KEY_ARROW_LEFT = 75;
const char KEY_ARROW_RIGHT = 77;

const char UNDERSCORE_BEGIN[] = "\033[4m";
const char UNDERSCORE_END[] = "\033[0m";