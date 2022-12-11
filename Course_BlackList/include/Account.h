#pragma once

#include <string>
#include <vector>

#include "FileHandle.hpp"

#include "common.h"

class Password
{
protected:
	std::string hash;
	std::string salt;

public:
	Password(std::string& hash, std::string& salt);
	Password(const Password& other) = default;
	Password(Password&& other) noexcept;
	Password();

	bool operator==(const Password& other) const;

	friend std::ofstream& operator<<(std::ofstream& ofs, const Password& obj);
	friend std::ifstream& operator>>(std::ifstream& ifs, Password& obj);

	friend std::ostream& operator<<(std::ostream& os, const Password& obj);

	bool same_as(std::string input);
};

Password make_password(std::string& input);
Password make_password(std::string&& input);


class Account
{
public:
	enum class Access
	{
		Denied,
		Pendig,
		Approved
	};
	static std::string Access_toString(Access acess);

	enum class Level
	{
		Client,
		Admin,
		Super
	};
	static std::string Level_toString(Level level);

protected:
	std::string id;
	std::string login;
	Password password;
	
public:
	Access access;
	Level level;

	friend std::ofstream& operator<< (std::ofstream& ofs, const Account& acc);
	friend std::ifstream& operator>> (std::ifstream& ofs, Account& acc);

	Account& operator=(const Account& other);
	Account& operator=(const Account&& other);


	std::string InfoRow (const int& count = 1) const;
	std::string InfoRow_highlight(const int& count) const;

	void PrintInfo_underscore(const int& count = 1);
	void PrintInfoWithTop();
	static std::string TopRow();

	Account();
	Account(const std::string& login,
		const std::string& id,
		const Password& password,
		const Access access,
		const Level level);
	Account(const Account& other) = default;
	Account(Account&& other) noexcept;

	void print();

	void setId(std::string&& id) { this->id = id; }
	void setLogin(std::string&& login) { this->login = login; }

	inline std::string getId() const { return id; }

private:
	static std::vector<std::shared_ptr<Account>> Vector;
	static size_t MAX_VECTOR_SIZE;
	static size_t RESERVE_SIZE;
	static size_t BUFFER_SIZE;
	static std::string path_accounts;

public:
	static void LoadFileToVector();
	static void SaveVectorToFile();

	static void vector_push(const Account& acc);
	static std::shared_ptr<Account> vector_get(size_t index);
	static void vector_print_highlight(size_t highlight_index);
	static void vector_print_highlight(size_t highlight_index, size_t first, size_t last);
};