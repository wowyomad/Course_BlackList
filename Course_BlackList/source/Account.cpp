#include "Account.h"

#include "RNG.hpp"

#include <iostream>

#include <assert.h>

#include "PrintFormat.h"
#include "console_manip.h"

std::vector<std::shared_ptr<Account>> Account::Vector;
size_t Account::MAX_VECTOR_SIZE;
size_t Account::RESERVE_SIZE;
size_t Account::BUFFER_SIZE;
std::string Account::path_accounts;

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


std::ofstream& operator<<(std::ofstream& ofs, const Account& acc)
{
	ofs << acc.id << ' ';
	ofs << acc.login << ' ';
	ofs << acc.password << ' ';
	ofs.write((const char*)&acc.access, sizeof(Account::Access));
	ofs.write((const char*)&acc.level, sizeof(Account::Level));
	//std::cout << ofs.tellp() << '\n';
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Account& acc)
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

Password make_password(std::string& input)
{
	std::string salt = RNG::GenerateNum_str();
	std::string hash = RNG::HashString_withSalt(input, salt);
	return Password(hash, salt);
}

Password make_password(std::string&& input)
{
	return make_password(input);
}

Password::Password(std::string& hash, std::string& salt)
	:hash(hash), salt(salt) {}

Password::Password()
	:hash("none"), salt("none") {}

Password::Password(Password&& other) noexcept
	: hash(std::move(other.hash)),
	salt(std::move(other.salt)) {}
		

bool Password::operator==(const Password& other) const
{
	return hash == other.hash and salt == other.salt;
}

bool Password::same_as(std::string input)
{
	return RNG::HashString_withSalt(input, salt) == hash;
}

std::ofstream& operator<<(std::ofstream& ofs, const Password& obj)
{
	ofs << obj.hash << ' ' << obj.salt;
	return ofs;
}
std::ifstream& operator>>(std::ifstream& ifs, Password& obj)
{
	ifs >> obj.hash >> obj.salt;
	return ifs;
}
std::ostream& operator<<(std::ostream& os, const Password& obj)
{
	os << "hash\t" << obj.hash << '\n'
		<< "salt\t" << obj.salt;
	return os;
}

std::string Account::TopRow()
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
	row.reserve(5);
	row.emplace_back(std::to_string(count));
	row.emplace_back(id);
	row.emplace_back(login);
	row.emplace_back(Account::Level_toString(level));
	row.emplace_back(Account::Access_toString(access));

	std::string info_row = RowString(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);
	//std::cout << ss.size() << '\n';

	return info_row;
} 

std::string Account::InfoRow_highlight(const int& count) const
{
	using namespace ConsoleFormat;

	std::vector <std::string> row;
	row.reserve(5);
	row.emplace_back(std::to_string(count));
	row.emplace_back(id);
	row.emplace_back(login);
	row.emplace_back(Account::Level_toString(level));
	row.emplace_back(Account::Access_toString(access));

	std::string info_row = RowString_highlight(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);
	//std::cout << ss.size() << '\n';

	return info_row;
}

void Account::PrintInfo_underscore(const int& count)
{
	using namespace ConsoleFormat;

	std::vector <std::string> row;
	row.reserve(4);
	row.emplace_back(std::to_string(count));
	row.emplace_back(login);
	row.emplace_back(Account::Level_toString(level));
	row.emplace_back(Account::Access_toString(access));

	PrintRow(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);
}


void Account::vector_push(const Account& acc)
{
	if (Account::Vector.size() >= Account::BUFFER_SIZE)
		Account::Vector.reserve(Vector.size() + Account::RESERVE_SIZE);

	//Account::Vector.emplace_back(acc);
}


std::shared_ptr<Account> Account::vector_get(size_t index)
{
	if (index >= Account::Vector.size())
		throw std::out_of_range("Индекс вне диапазона массива аккаунтов");

	return Account::Vector[index];
}
void Account::vector_print_highlight(size_t highlight_index)
{
	size_t size = Account::Vector.size();
	if (size <= 0) return;

	Account::TopRow();

	for (size_t i = 0; i < size; i++)
	{
		if (i == highlight_index)
		{
			std::cout << manip::bg_green_bright << '\r';
			std::cout << Account::Vector[i]->InfoRow();
			std::cout << manip::reset;
		}
	}
}

void Account::vector_print_highlight(size_t highlight_index, size_t first, size_t last)
{
	
}