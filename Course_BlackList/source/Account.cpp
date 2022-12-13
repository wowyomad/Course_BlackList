#include "Account.h"

#include <iostream>
#include <memory>

#include <assert.h>

#include "PrintFormat.h"
#include "console_manip.h"
#include "RNG.hpp"

#include "FileHandle.hpp"

std::vector<std::shared_ptr<Account>> Account::vector;
size_t Account::MAX_VECTOR_SIZE;
size_t Account::RESERVE_SIZE;
size_t Account::BUFFER_SIZE;

void Account::print()
{
	std::cout << "Логин\t" << login << '\n'
		<< "id\t" << id << '\n'
		<< "Доступ\t" << Access_toString(access) << '\n'
		<< "Уровень\t" << Level_toString(level) << '\n'
		<< password << '\n';
}

std::string Account::Access_toString(Account::Access access)
{
	using Access = Account::Access;
	switch (access)
	{
	case Access::Denied:
		return "Запрещён";
	case Access::Approved:
		return "Разрешён";
	case Access::Pendig:
		return "Ожидание";
	}
}

std::string Account::Level_toString(Account::Level level)
{
	using Level = Account::Level;
	switch (level)
	{
	case Level::Client:
		return "Клиент";
	case Level::Admin:
		return "Админ";
	case Level::Super:
		return "Суперпользователь";
	}
}

Account::Account()
	: id("none"), password(), access(), level() {}

Account::Account(const std::string& login,
	const std::string& id,
	const Password& password,
	const Access access,
	const Level level)
	: login(login), id(id), password(password), access(access), level(level) {}

Account::Account(Account&& other) noexcept
	: login(std::move(other.login)),
	id(std::move(other.id)),
	password(std::move(other.password)),
	access(other.access),
	level(other.level)
{}


std::fstream& operator<<(std::fstream& ofs, const Account& acc)
{
	ofs << acc.id << ' ';
	ofs << acc.login << ' ';
	ofs << acc.password << ' ';
	ofs.write((const char*)&acc.access, sizeof(Account::Access));
	ofs.write((const char*)&acc.level, sizeof(Account::Level));
	//std::cout << ofs.tellp() << '\n';
	return ofs;
}

std::fstream& operator>>(std::fstream& ifs, Account& acc)
{
	ifs >> acc.id;
	ifs >> acc.login;
	ifs >> acc.password;
	ifs.get();
	ifs.read((char*)&acc.access, sizeof(Account::Access));
	ifs.read((char*)&acc.level, sizeof(Account::Level));
	//std::cout << ifs.tellg() << '\n';
	return ifs;
}

bool Account::UpdateLogin(const std::string& login)
{
	if (Account::login_is_uniqiue(login))
	{
		this->login = login;
		return true;
	}
	return false;
}

void Account::UpdatePassword(const std::string& password_string)
{
	this->password = make_password(password_string);
}


std::string Account::TopRow_num()
{
	using namespace ConsoleFormat;
	std::vector<std::string> row;
	row.reserve(5);
	row.emplace_back("Номер");
	row.emplace_back("ID");
	row.emplace_back("Логин");
	row.emplace_back("Уровень");
	row.emplace_back("Доступ");

	return ConsoleFormat::RowString(row, BORDER::BOTTOM);
}

std::string Account::TopRow()
{
	using namespace ConsoleFormat;
	std::vector<std::string> row;
	row.reserve(4);
	row.emplace_back("ID");
	row.emplace_back("Логин");
	row.emplace_back("Уровень");
	row.emplace_back("Доступ");

	return ConsoleFormat::RowString(row, BORDER::BOTTOM);
}



Account& Account::operator=(const Account& other)
{
	this->id = other.id;
	this->login = other.login;
	this->password = other.password;
	this->access = other.access;
	this->level = other.level;
	return *this;
}

Account& Account::operator=(const Account&& other)
{
	this->id = std::move(other.id);
	this->login = std::move(other.login);
	this->password = std::move(other.password);
	this->access = std::move(other.access);
	this->level = std::move(other.level);
	return *this;
}

std::string Account::InfoRow(const int& count) const
{
	using namespace ConsoleFormat;

	std::vector <std::string> row;
	if (count > 0)
	{
		row.reserve(5);
		row.emplace_back(std::to_string(count));
	}
	else
	{
		row.reserve(4);
	}
	row.emplace_back(id);
	row.emplace_back(login);
	row.emplace_back(Account::Level_toString(level));
	row.emplace_back(Account::Access_toString(access));

	std::string info_row = RowString(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);

	return info_row;
}

std::string Account::InfoRow_highlight(const int& count) const
{
	using namespace ConsoleFormat;

	std::vector <std::string> row;
	if (count > 0)
	{
		row.reserve(5);
		row.emplace_back(std::to_string(count));
	}
	else
	{
		row.reserve(4);
	}
	row.emplace_back(id);
	row.emplace_back(login);
	row.emplace_back(Account::Level_toString(level));
	row.emplace_back(Account::Access_toString(access));

	std::string info_row = RowString_highlight(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);

	return info_row;
}

std::shared_ptr<Account> Account::vector_get(size_t index)
{
	if (index >= Account::vector.size())
		throw std::out_of_range("Индекс вне диапазона массива аккаунтов");

	return Account::vector[index];
}

std::shared_ptr<Account> Account::vector_get(std::string login)
{
	size_t i = 0;
	for (const std::shared_ptr<Account> acc : vector)
	{
		if (acc->login == login)
			return vector[i];
		i++;
	}
	throw std::out_of_range("Такого пользователя нет в массиве");
}

void Account::vector_print_highlight(size_t highlight_index)
{
	size_t size = Account::vector.size();
	if (size <= 0) return;

	vector_print_highlight(highlight_index, 0, size);
}

void Account::vector_print_highlight(size_t highlight_index, size_t first, size_t amount)
{
	std::cout << Account::TopRow_num();

	if (first < 0 or first >= vector.size())
		throw std::out_of_range("fdsffdf");

	if (amount <= 0 or (first + amount) > vector.size())
		throw std::out_of_range("123213");

	size_t last = first + amount;

	for (size_t i = first; i < last; i++)
	{
		if (i == highlight_index)
		{
			std::cout << Account::vector[i]->InfoRow_highlight(i + 1);
		}
		else
		{
			std::cout << Account::vector[i]->InfoRow(i + 1);
		}
	}
}

std::string Account::GenerateId()
{
	std::vector<std::size_t>taken_ids(vector.size());
	for (size_t i = 0; i < vector.size(); i++)
	{
		taken_ids[i] = static_cast<size_t>(std::atoll(vector[i]->id.c_str()));
	}
	std::string id = std::to_string(RNG::GenerateNum_check(taken_ids));
	return id;
}
void Account::CreateNewFile()
{
	std::ofstream file(PATH::Accounts);
	if (!file.is_open())
		throw "wtf";
	file.close();
}

bool Account::ReadFile()
{
	vector.clear();
	vector.reserve(RESERVE_SIZE);

	if (GetFileStatus() == FileStatus::Opened)
		return File::ReadFile(PATH::Accounts, vector);

	return false;
}

bool Account::WriteFile()
{
	return File::WriteToFile(PATH::Accounts, vector);
}

void Account::CopyVector(std::vector<std::shared_ptr<Account>>& destination)
{
	destination.clear();
	destination.reserve(vector.size());
	for (const std::shared_ptr<Account>& it : vector)
	{
		destination.emplace_back(it);
	}
}

const std::vector<std::shared_ptr<Account>> Account::vector_ref()
{
	return vector;
}


void Account::vector_push(const Account& acc)
{
	if (Account::vector.size() >= Account::BUFFER_SIZE)
		Account::vector.reserve(vector.size() + Account::RESERVE_SIZE);

	std::shared_ptr<Account> new_account = std::make_shared<Account>(acc);
	Account::vector.emplace_back(new_account);
}

std::shared_ptr<Account> Account::GetAccount(const int index)
{
	if (index > vector.size() - 1) throw "wtf index";
	return vector[index];
}

std::shared_ptr<Account> Account::GetAccount(const std::string login)
{
	for (std::shared_ptr<Account>& it : vector)
		if (it->login == login)
			return it;
	throw "wtf login not found";
}

void Account::RemoveUser(const size_t index)
{
	if (index > vector.size() - 1) throw "wtf index";

	vector.erase(vector.begin() + index);
}
bool Account::login_is_uniqiue(const std::string& login)
{
	for (const std::shared_ptr<Account>& acc : vector)
		if (acc->login == login)
			return false;
	return true;
}

FileStatus Account::GetFileStatus()
{
	return FileStatus::Opened;
}

Account make_account(const std::string& login, const std::string& string_password, const Account::Access access, const Account::Level level)
{
	Password password = make_password(string_password);
	std::string id = Account::GenerateId();
	return Account(login, id, password, access, level);
}

Account make_account_client(const std::string& login, const std::string& string_password)
{
	return make_account(login, string_password, Account::Access::Pendig, Account::Level::Client);
}

Account make_account_client_approved(const std::string& login, const std::string& string_password)
{
	return make_account(login, string_password, Account::Access::Approved, Account::Level::Client);
}

Account make_account_admin(const std::string& login, const std::string& string_password)
{
	return make_account(login, string_password, Account::Access::Approved, Account::Level::Admin);
}

