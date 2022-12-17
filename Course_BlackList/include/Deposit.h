#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Printable.h"
#include "TableInterface.hpp"
#include "FileHandle.hpp"
#include "Money.hpp"
#include "RNG.hpp"
#include "Date.h"

using Money = long long;

class Deposit : public Printable
{
public:
	std::string title;
	std::string id;
	float int_rate;
	Money deposit_min;
	Money deposit_max;

	static std::vector<std::shared_ptr<Deposit>> vector;

public:

	static bool ReadFile();
	static bool WriteFile();
	static FileStatus GetFileStatus();

	virtual void print_topRow_index() const override;
	static void print_TopRow_index();

	virtual void print_row(const size_t& index) const override;
	virtual void print_row_index(const size_t& index) const override;
	virtual void print_row_highlight(const size_t& index) const override;
	virtual void print_row_index_highlight(const size_t& index) const override;

	Deposit(const std::string& title,
		const std::string& id, 
		const float int_rate, 
		const Money min,
		const Money max);

	Deposit() = default;
	Deposit(const Deposit& other) = default;
	Deposit(Deposit&& other) = default;

	Deposit operator=(const Deposit& other);
	Deposit operator=(Deposit&& other);

	bool operator==(const Deposit& other);
	bool operator==(const std::string& id);


	friend std::fstream& operator<<(std::fstream& fs, const Deposit& deposit);
	friend std::fstream& operator>>(std::fstream& fs,  Deposit& deposit);

	static void vector_push(const Deposit& deposit);
	static const std::vector<std::shared_ptr<Deposit>> vector_ref();
	static Deposit get_deposit(const size_t index);
};

Deposit make_deposit(const std::string& title,
	const float int_rate, 
	const Money min,
	const Money max);

class ClientDeposit : public Printable
{
	std::string id;
	std::string title;

	TimeDate date_start;
	TimeDate date_end_planned;
	TimeDate date_end_real;

	Money invested;
	Money planned;
	Money real;

	float int_rate;
	bool finished;

public:
	ClientDeposit(const std::string& title,
		const std::string& id,
		float int_rate,
		bool finished,
		Money invested,
		Money planned,
		Money real,
		const TimeDate date_start,
		const TimeDate date_end_planned,
		const TimeDate date_end_real);

	ClientDeposit() = default;

	virtual void print_topRow_index() const override;
	static void print_TopRow_index();

	virtual void print_row(const size_t& index) const override;
	virtual void print_row_index(const size_t& index) const override;
	virtual void print_row_highlight(const size_t& index) const override;
	virtual void print_row_index_highlight(const size_t& index) const override;

	friend std::fstream& operator<<(std::fstream& fs, const ClientDeposit& deposit);
	friend std::fstream& operator>>(std::fstream& fs,  ClientDeposit& deposit);

	void finish_now();
	bool is_finished();

	static ClientDeposit make_from_deposit(const Deposit& deposit, Money investment, unsigned days);

};

ClientDeposit make_client_deposit(std::string title, 
	const Money invested,
	const float int_rate,
	const TimeDate date_start,
	const unsigned days);