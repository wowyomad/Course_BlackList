#pragma once
#include "PrintFormat.h"	

#include "Deposit.h"

namespace message
{
	using message = std::string;

	static message _HelloScreen_hello = "Добро пожаловать в ад";
	static message _HelloScreen_header = "Меню входа/регистрации";
	static message _HelloScreen_register = "Регистрация";
	static message _HelloScreen_login = "Логин";

}

namespace UI
{
	void HelloScreen();

	void Login();
	void Register();

	void PrintHeader(const message::message& name);
	void PrintOption(const message::message& option);
	void PrintMessage(const message::message& message);
	void PrintOption_highlight(const message::message& option);
	void PrintLine(const char character = '-');

	void WaitTillEnter();
}


using event = uint8_t;
namespace events
{
	static const event none = 0x00000000;
	static const event select = 0x00000001;
	static const event back = 0x00000002;
}

class OptionsInterface
{
	unsigned short pos;
	unsigned short max_pos;
	COORD home;
	event last_event;
	std::vector<std::string> options;

public:
	void update();
	void render();

	event event() const;
	unsigned short position() const;
	

	OptionsInterface(const std::vector<std::string>& options, COORD home);

private:
	void move_up();
	void move_down();

};