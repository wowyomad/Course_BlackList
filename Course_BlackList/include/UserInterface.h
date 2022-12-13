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
	bool to_update;
	std::vector<std::string> options;
	std::string header;

public:
	void update();
	void render();

	event event() const;
	unsigned short position() const;
	

	OptionsInterface(const std::vector<std::string>& options, COORD home);
	OptionsInterface(const std::vector<std::string>& options, const std::string& header, COORD home);
private:
	void move_up();
	void move_down();

};

class TableInterface
{
protected:
	size_t pos;
	size_t size;
	size_t max_pos;

	size_t page;
	size_t max_page;

	COORD home;
	event last_event;
	const size_t rows;
	bool to_update;


public:
	void update();
	virtual void render() = 0;

	virtual void refresh() = 0;
	
	size_t index() const;
	virtual event event() const;

	TableInterface(COORD home, size_t rows);

private:

	void move_left();
	void move_right();
	void move_up();
	void move_down();
};

class TI_accounts : public TableInterface
{
	std::vector<std::pair<size_t, std::shared_ptr<Account>>> accounts;
	const std::vector<std::shared_ptr<Account>> origin_ref;


public:
	TI_accounts(const std::vector<std::shared_ptr<Account>>& origin, const size_t rows, COORD home);

	virtual void refresh() override;
	virtual void render() override;

};

