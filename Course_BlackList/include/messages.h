#pragma once

#include <string>
namespace message
{
	using msg = std::string;

	static const msg _HelloScreen_hello = "����� ���������� � ��";
	static const msg _HelloScreen_header = "���� �����/�����������";

	static const msg _MainScreen_header = "������� ����";
	static const msg _MainScreen_register = "�����������";
	static const msg _MainScreen_login = "�����";


	static const msg _MainScreen_no_super_user = "������� ����������������� �� ���������";
	static const msg _MainScreen_register_as_super = "�� ������ �������������� �� ����������� �������� �����������������";


	static const msg _Login_header = "���� � �������";
	static const msg _Login_fail = "�������� ����� ��� ������";
	static const msg _Login_unavailable = "������� �������� ����������";
	static const msg _Login_success = "�� ������� ����� � �������";
	static const msg _Login_back = "������ ��������� �������?";



	static const msg _Register_header = "����������� ��������";
	static const msg _Register_available = "����� �������� ��� �����������";
	static const msg _Register_unavailable = "����� �� �������� ��� �����������";
	static const msg _Register_confirm = "����������� �����������";
	static const msg _Register_success = "������� ��� ������� ������";
	static const msg _Register_fail = "������� �� ��� ������";
	static const msg _Register_back = "������ ��������� �������?";


	static const msg _Super_header = "���� �����������������";
	static const msg _Admin_header = "���� ��������������";
	static const msg _Client_header = "���� �������";



	static const msg _key_enter = "ENTER";
	static const msg _key_esc = "ESC";

	static const msg _back = "����� - " + _key_esc;
	static const msg _exit = "����� - " + _key_esc;
	static const msg _select = "����� - " + _key_enter;

	static const msg _accept = "������������ - " + _key_enter;
	static const msg _decline = "�������� - " + _key_esc;
}