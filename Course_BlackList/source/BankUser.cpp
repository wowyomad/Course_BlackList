#include "BankUser.h"



Client::Client(const std::string& name,
	const std::string& id,
	const std::vector<std::shared_ptr<ClientDeposit>> deposits)
	:name(name), id(id), deposits(deposits)
{

}

void Client::ReadFile()
{

}
void Client::WriteFile()
{

}

void Client::print_topRow_index() const
{

}

void Client::print_row(const size_t& index) const
{

}
void Client::print_row_index(const size_t& index) const
{

}
void Client::print_row_highlight(const size_t& index) const
{

}
void Client::print_row_index_highlight(const size_t& index) const
{

}

std::fstream& operator<<(std::fstream& fs, const Client& client)
{
	fs << client.name << ' ';
	fs << client.id << ' ';
	size_t size = client.deposits.size();
	fs.write((char*)&size, sizeof(size_t));
	for (const auto& deposit : client.deposits)
		fs << *deposit;
	return fs;
}

std::fstream& operator>>(std::fstream& fs, Client& client)
{
	fs >> client.name;
	fs >> client.id;
	fs.get();
	size_t size;
	fs.read((char*)&size, sizeof(size_t));
	client.deposits.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		ClientDeposit deposit;
		fs >> deposit;
		client.deposits[i] = std::make_shared<ClientDeposit>(deposit);
	}
	return fs;
}

Client Client::make_from_account(const std::shared_ptr<Account>& acc)
{
	std::vector<std::shared_ptr<ClientDeposit>> deposits;

	return Client(acc->get_login(), acc->get_id(), deposits);
}