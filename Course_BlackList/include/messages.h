#pragma once

#include <string>
namespace message
{
	using msg = std::string;

	static const msg _HelloScreen_hello = "Добро пожаловать в ад";
	static const msg _HelloScreen_header = "Меню входа/регистрации";

	static const msg _MainScreen_header = "Главное меню";
	static const msg _MainScreen_register = "Регистрация";
	static const msg _MainScreen_login = "Логин";


	static const msg _MainScreen_no_super_user = "Аккаунт суперпользователя не обнаружен";
	static const msg _MainScreen_register_as_super = "Вы будете перенаправлены на регистрацию аккаунта суперпользователя";


	static const msg _Login_header = "Вход в аккаунт";
	static const msg _Login_fail = "Неверный логин или пароль";
	static const msg _Login_unavailable = "Аккаунт временно недоступен";
	static const msg _Login_success = "Вы успешно вошли в аккаунт";
	static const msg _Login_back = "Хотите повторить попытку?";



	static const msg _Register_header = "Регистрация аккаунта";
	static const msg _Register_available = "Логин доступен для регистрации";
	static const msg _Register_unavailable = "Логин не доступен для регистрации";
	static const msg _Register_confirm = "Подтвердите регистрацию";
	static const msg _Register_success = "Аккаунт был успешно создан";
	static const msg _Register_fail = "Аккаунт не был создан";
	static const msg _Register_back = "Хотите повторить попытку?";


	static const msg _Super_header = "Меню суперпользователя";
	static const msg _Admin_header = "Меню администратора";
	static const msg _Client_header = "Меню клиента";



	static const msg _key_enter = "ENTER";
	static const msg _key_esc = "ESC";

	static const msg _back = "Назад - " + _key_esc;
	static const msg _exit = "Выход - " + _key_esc;
	static const msg _select = "Выбор - " + _key_enter;

	static const msg _accept = "ПОДТВЕРИДИТЬ - " + _key_enter;
	static const msg _decline = "ОТМЕНИТЬ - " + _key_esc;
}