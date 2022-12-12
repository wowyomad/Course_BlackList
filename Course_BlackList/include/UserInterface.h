#pragma once
#include "PrintFormat.h"	
#include "Account.h"
#include "Deposit.h"

namespace message
{
	using message = std::string;

	static const message _HelloScreen_hello = "Добро пожаловать в ад";
	static const message _HelloScreen_header = "Меню входа/регистрации";

	static const message _MainScreen_header = "Главное меню";
	static const message _MainScreen_register = "Регистрация";
	static const message _MainScreen_login = "Логин";

	static const message _Login_header = "Вход в аккаунт";
	static const message _Login_fail = "Неверный логин или пароль";
	static const message _Login_unavailable = "Аккаунт временно недоступен";
	static const message _Login_success = "Вы успешно вошли в аккаунт";
	static const message _Login_back = "Хотите повторить попытку?";



	static const message _Register_header = "Регистрация аккаунта";
	static const message _Register_available = "Логин доступен для регистрации";
	static const message _Register_unavailable = "Логин не доступен для регистрации";
	static const message _Register_confirm = "Подтвердите регистрацию";
	static const message _Register_success = "Аккаунт был успешно создан";
	static const message _Register_fail = "Аккаунт не был создан";
	static const message _Register_back = "Хотите повторить попытку?";


	static const message _Super_header = "Меню суперпользователя";
	static const message _Admin_header = "Меню администратора";
	static const message _Client_header = "Меню клиента";


		   
	static const message _key_enter = "ENTER";
	static const message _key_esc = "ESC";

	static const message _back = "Назад - " + _key_esc;
	static const message _exit = "Выход - " + _key_esc;
	static const message _select = "Выбор - " + _key_enter;

	static const message _accept = "ПОДТВЕРИДИТЬ - " + _key_enter;
	static const message _decline = "ОТМЕНИТЬ - " + _key_esc;
}

namespace UI
{
	void HelloScreen();

	void MainScreen();

	void Login();
	void Register(const Account::Level level);

	void Main_Super(std::shared_ptr<Account> account_ptr);
	void Main_Admin(std::shared_ptr<Account> account_ptr);
	void Main_Client(std::shared_ptr<Account> account_ptr);

	void PrintHeader(const message::message& name);
	void PrintOption(const message::message& option);
	void PrintMessage(const message::message& message);
	void PrintOption_highlight(const message::message& option);
	void PrintLine(const char character = '-');

	void PrintEnter();
	void PrintEsc();
	void PrintAccept();
	void PrintDecline();

	bool UserAccept();
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

class TableInterface
{
protected:
	size_t pos;
	size_t max_pos;

	size_t page;
	size_t max_page;

public:
	virtual void update() = 0;
	virtual void render() = 0;
	
	size_t index() const;

	TableInterface();
};

class TableInterface_accounts : public TableInterface
{


};

