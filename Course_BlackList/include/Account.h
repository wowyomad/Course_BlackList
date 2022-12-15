#pragma once

#include <string>
#include <vector>
#include <memory>

#include "common.h"

#include "Password.h"
#include "FileHandle.hpp"

#include "Printable.h"


class Account : public Printable
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


	std::string row_index(const size_t& index) const;

	std::string row_highlight_index(const size_t& index) const;

	virtual void print_row(const size_t& index) const override;
	virtual void print_row_index(const size_t& index) const override;
	virtual void print_row_highlight(const size_t& index) const override;
	virtual void print_row_index_highlight(const size_t& index) const override;

	virtual void print_topRow_index() const override;
	static std::string TopRow();


	Account();
	Account(const std::string& login,
		const std::string& id,
		const Password& password,
		const Access access,
		const Level level);
	Account(const Account& other) = default;
	Account(Account&& other) noexcept;

	void set_id(const std::string& id) { this->id = id; }
	void set_login(const std::string& login) { this->login = login; }

	bool UpdateLogin(const std::string& login);
	void UpdatePassword(const std::string& password_string);

	inline std::string get_id() const { return id; }
	inline std::string get_login() const { return login; }
	inline Password get_password() const { return password; }
	//size_t get_index() const;


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
	static std::shared_ptr<Account> get_account(size_t index);
	static std::shared_ptr<Account> get_account(std::string login);

	static void print_table_highlight(size_t highlight_index);
	static void print_table_highlight(size_t highlight_index, size_t first, size_t amount);

	static bool login_is_uniqiue(const std::string& login);
	static std::string GenerateId();
};

Account make_account(const std::string& login, const std::string& string_password, const Account::Access access, const Account::Level level);
Account make_account_client(const std::string& login, const std::string& string_password);
Account make_account_client_approved(const std::string& login, const std::string& string_password);
Account make_account_admin(const std::string& login, const std::string& string_password);