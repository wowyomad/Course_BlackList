#pragma once

#include "Money.hpp"

#include <string>


class BankClient
{
	using Money = Money_64 < '.'>;
protected:
	std::string login;
	std::string id;
	Money current_balance;

};