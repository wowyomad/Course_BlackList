#include "BankUser.h"

#include "common.h"

Client::Client(const std::string& name,
	const std::string& id,
	const std::vector<std::shared_ptr<ClientDeposit>> deposits)
	:name(name), id(id), deposits(deposits)
{

}

bool Client::ReadFile()
{
	vector.clear();
	vector.reserve(CONSTANT::RESERVE_SIZE);

	if (GetFileStatus() == FileStatus::Opened)
		return File::ReadFile(PATH::Clients, vector);

	return false;

}
bool Client::WriteFile()
{
	return File::WriteToFile(PATH::Clients, vector);
}

FileStatus Client::GetFileStatus()
{
	return FileStatus::Opened;
}

void Client::add_deposit(const ClientDeposit& deposit)
{
	deposits.push_back(std::make_shared<ClientDeposit>(deposit));
}

const std::vector<std::shared_ptr<ClientDeposit>> Client::get_deposit_ref() const
{
	return deposits;
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

const std::vector<std::shared_ptr<Client>> Client::vector_ref()
{
	return vector;
}
void Client::vector_push(const Client& acc)
{
	if (Client::vector.size() == CONSTANT::RESERVE_SIZE)
		Client::vector.reserve(vector.size() + CONSTANT::RESERVE_SIZE);

	std::shared_ptr<Client> new_account = std::make_shared<Client>(acc);
	Client::vector.emplace_back(new_account);
}
std::shared_ptr<Client> Client::get_account(size_t index)
{
	if (index > vector.size() - 1) throw "wtf index";
	return vector[index];
}
std::shared_ptr<Client> Client::get_account(std::string login)
{
	for (std::shared_ptr<Client>& it : vector)
		if (it->id == login)
			return it;
	throw "wtf login not found";
}

void Client::RemoveUser(const size_t index)
{
	if (index > vector.size() - 1) throw "wtf index";

	vector.erase(vector.begin() + index);
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