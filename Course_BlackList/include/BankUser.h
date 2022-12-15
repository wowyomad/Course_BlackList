#pragma once

#include "Money.hpp"
#include "Account.h"

#include <string>


class BankClient
{
	using Money = Money_64 < '.'>;
protected:
	const std::shared_ptr<Account> this_account;
	Money current_balance;

};