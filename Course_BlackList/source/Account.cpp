#include "Account.h"

#include <iostream>
#include <memory>

#include <assert.h>

#include "PrintFormat.h"
#include "console_manip.h"

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

void Account::UpdatePassword(const std::string& newPassword)
{
	this->password = make_password(newPassword);
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
	Account acc(other);
	return acc;
}

Account& Account::operator=(const Account&& other)
{
	Account acc(other);
	return acc;
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

void Account::PrintVector_highlight(const size_t index)
{
	std::cout << Account::TopRow_num();

	std::vector<std::string> row;
	size_t i = 1;
	for (auto& acc : vector)
	{
		if (i - 1 == index)
			std::cout << acc->InfoRow_highlight(i);
		else
			std::cout << acc->InfoRow(i);
		i++;
	}
}


std::shared_ptr<Account> Account::vector_get(size_t index)
{
	if (index >= Account::vector.size())
		throw std::out_of_range("Индекс вне диапазона массива аккаунтов");

	return Account::vector[index];
}
void Account::vector_print_highlight(size_t highlight_index)
{
	size_t size = Account::vector.size();
	if (size <= 0) return;

	vector_print_highlight(highlight_index, 0, size);
}

void Account::vector_print_highlight(size_t highlight_index, size_t first, size_t last)
{
	std::cout << Account::TopRow_num();

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


FileStatus Account::GetFileStatus()
{
	return FileStatus::Opened;
}