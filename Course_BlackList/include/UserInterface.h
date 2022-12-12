#pragma once
#include "PrintFormat.h"	
#include "Account.h"
#include "Deposit.h"

namespace message
{
	using message = std::string;

	static const message _HelloScreen_hello = "����� ���������� � ��";
	static const message _HelloScreen_header = "���� �����/�����������";

	static const message _MainScreen_header = "������� ����";
	static const message _MainScreen_register = "�����������";
	static const message _MainScreen_login = "�����";

	static const message _Login_header = "���� � �������";
	static const message _Login_fail = "�������� ����� ��� ������";
	static const message _Login_unavailable = "������� �������� ����������";
	static const message _Login_success = "�� ������� ����� � �������";
	static const message _Login_back = "������ ��������� �������?";



	static const message _Register_header = "����������� ��������";
	static const message _Register_available = "����� �������� ��� �����������";
	static const message _Register_unavailable = "����� �� �������� ��� �����������";
	static const message _Register_confirm = "����������� �����������";
	static const message _Register_success = "������� ��� ������� ������";
	static const message _Register_fail = "������� �� ��� ������";
	static const message _Register_back = "������ ��������� �������?";


	static const message _Super_header = "���� �����������������";
	static const message _Admin_header = "���� ��������������";
	static const message _Client_header = "���� �������";


		   
	static const message _key_enter = "ENTER";
	static const message _key_esc = "ESC";

	static const message _back = "����� - " + _key_esc;
	static const message _exit = "����� - " + _key_esc;
	static const message _select = "����� - " + _key_enter;

	static const message _accept = "������������ - " + _key_enter;
	static const message _decline = "�������� - " + _key_esc;
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

