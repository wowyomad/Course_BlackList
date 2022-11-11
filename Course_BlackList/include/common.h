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