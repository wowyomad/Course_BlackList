#pragma once

#include <string>
#include <vector>
#include <memory>

#include "common.h"

#include "Password.h"
#include "FileHandle.hpp"


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

	friend std::fstream& operator<< (std::fstream& ofs, const Account& acc);
	friend std::fstream& operator>> (std::fstream& ofs, Account& acc);

	Account& operator=(const Account& other);
	Account& operator=(const Account&& other);


	std::string InfoRow(const int& count = 0) const;
	std::string InfoRow_highlight(const int& count = 0) const;

	static std::string TopRow_num();
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

	void setId(const std::string& id) { this->id = id; }
	void setLogin(const std::string& login) { this->login = login; }

	bool UpdateLogin(const std::string& login);
	void UpdatePassword(const std::string& password_string);

	inline std::string getId() const { return id; }
	inline std::string getLogin() const { return login; }
	inline Password getPassword() const { return password; }


private:
	static std::vector<std::shared_ptr<Account>> vector;
	static size_t MAX_VECTOR_SIZE;
	static size_t RESERVE_SIZE;
	static size_t BUFFER_SIZE;

public:
	static void CreateNewFile();
	static bool ReadFile();
	static bool WriteFile();
	static FileStatus GetFileStatus();

	static void CopyVector(std::vector <std::shared_ptr<Account>>& dest);
	static void RemoveUser(const size_t index);
	static std::shared_ptr<Account> GetAccount(const int index);
	static std::shared_ptr<Account> GetAccount(std::string login);
	static size_t GetUserIndex(std::string login);

	static const std::vector<std::shared_ptr<Account>> vector_ref();
	static void vector_push(const Account& acc);
	static std::shared_ptr<Account> vector_get(size_t index);
	static std::shared_ptr<Account> vector_get(std::string login);
	static void vector_print_highlight(size_t highlight_index);
	static void vector_print_highlight(size_t highlight_index, size_t first, size_t amount);

	static bool login_is_uniqiue(const std::string& login);
	static std::string GenerateId();
};

Account make_account(const std::string& login, const std::string& string_password, const Account::Access access, const Account::Level level);
Account make_account_client(const std::string& login, const std::string& string_password);
Account make_account_client_approved(const std::string& login, const std::string& string_password);
Account make_account_admin(const std::string& login, const std::string& string_password);