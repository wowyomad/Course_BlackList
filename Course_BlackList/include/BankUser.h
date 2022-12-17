#pragma once

#include "Money.hpp"
#include "Deposit.h"
#include "FileHandle.hpp"

#include "Printable.h"

#include <string>
#include <vector>

using Money = long long;


class Client : public Printable
{
public:
	std::string name;
	std::string id;
	std::vector<std::shared_ptr<ClientDeposit>> deposits;

	static std::vector<std::shared_ptr<Client>> vector;

public:

	static bool ReadFile();
	static bool WriteFile();
	static FileStatus GetFileStatus();

	void add_deposit(const ClientDeposit& deposit);

	const std::vector<std::shared_ptr<ClientDeposit>> deposit_ref() const;

	virtual void print_topRow_index() const override;
	static void print_TopRow_index();
	virtual void print_row(const size_t& index) const override;
	virtual void print_row_index(const size_t& index) const override;
	virtual void print_row_highlight(const size_t& index) const override;
	virtual void print_row_index_highlight(const size_t& index) const override;

	static const std::vector<std::shared_ptr<Client>> vector_ref();
	static void vector_push(const Client& acc);
	static std::shared_ptr<Client> get_account(size_t index);
	static std::shared_ptr<Client> get_account(std::string login);

	static void RemoveUser(const size_t index);


	Client() = default;
	Client(const Client& client) = default;
	Client(const std::string& name, const std::string& id);

	Client(const std::string& name,
		const std::string& id,
		const std::vector<std::shared_ptr<ClientDeposit>> deposits);

	Client operator=(const Client& other);
	Client operator=(Client&& other);

	friend std::fstream& operator<<(std::fstream& fs, const Client& client);
	friend std::fstream& operator>>(std::fstream& fs, Client& client);
};