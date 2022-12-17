#include "Deposit.h"

#include <fstream>
#include <iostream>

#include "PrintFormat.h"

std::vector<std::shared_ptr<Deposit>> Deposit::vector;

bool Deposit::ReadFile()
{
	vector.clear();
	vector.reserve(CONSTANT::RESERVE_SIZE);

	if (GetFileStatus() == FileStatus::Opened)
		return File::ReadFile(PATH::Bank, vector);

	return false;
}

bool Deposit::WriteFile()
{
	return File::WriteToFile(PATH::Bank, vector);
}

FileStatus Deposit::GetFileStatus()
{
	return FileStatus();
}

void Deposit::print_topRow_index() const
{

}

void Deposit::print_TopRow_index() 
{
	using namespace ConsoleFormat;

	std::vector<std::string> top_row{
		"Название",
		"id",
		"Ставка, %",
		"мин. вклад",
		"макс. вклад"
	};

	ConsoleFormat::PrintRow(top_row, BORDER::BOTTOM);

}

void Deposit::print_row(const size_t& index) const
{

}

void Deposit::print_row_index(const size_t& index) const
{
	using namespace ConsoleFormat;

	std::vector<std::string> row{
		title,
		id,
		(std::stringstream() << std::fixed << std::setprecision(2) << int_rate).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << deposit_min).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << deposit_max).str()
	};

	ConsoleFormat::PrintRow(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);
}

void Deposit::print_row_highlight(const size_t& index) const
{

}

void Deposit::print_row_index_highlight(const size_t& index) const
{
	using namespace ConsoleFormat;

	std::vector<std::string> row{
		title,
		id,
		(std::stringstream() << std::fixed << std::setprecision(2) << int_rate).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << deposit_min).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << deposit_max).str()
	};

	ConsoleFormat::PrintRow_highlight(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);

}

Deposit::Deposit(const std::string& title, const std::string& id, const float int_rate, const Money min, const Money max)
	: title(title), id(id), int_rate(int_rate), deposit_min(min), deposit_max(max)
{

}


Deposit Deposit::operator=(const Deposit& other)
{
	return Deposit(other);
}

Deposit Deposit::operator=(Deposit&& other)
{
	return Deposit(other);
}

bool Deposit::operator==(const Deposit& other)
{
	return false;
}

bool Deposit::operator==(const std::string& id)
{
	return false;
}

void Deposit::vector_push(const Deposit& deposit)
{
	if (Deposit::vector.size() == CONSTANT::RESERVE_SIZE)
		Deposit::vector.reserve(vector.size() + CONSTANT::RESERVE_SIZE);

	std::shared_ptr<Deposit> new_deposit = std::make_shared<Deposit>(deposit);
	Deposit::vector.emplace_back(new_deposit);
}

const std::vector<std::shared_ptr<Deposit>> Deposit::vector_ref()
{
	return vector;
}

Deposit Deposit::get_deposit(const size_t index)
{
	return *vector[index];
}

std::fstream& operator<<(std::fstream& fs, const Deposit& deposit)
{
	fs << deposit.title << ' ';
	fs << deposit.id << ' ';
	fs.write((char*)&deposit.int_rate, sizeof(float));
	fs.write((char*)&deposit.deposit_min, sizeof(Money));
	fs.write((char*)&deposit.deposit_max, sizeof(Money));

	return fs;
}

std::fstream& operator>>(std::fstream& fs,  Deposit& deposit)
{
	fs >> deposit.title;
	fs >> deposit.id;
	fs.get();
	fs.read((char*)&deposit.int_rate, sizeof(float));
	fs.read((char*)&deposit.deposit_min, sizeof(Money));
	fs.read((char*)&deposit.deposit_max, sizeof(Money));

	return fs;
}

ClientDeposit::ClientDeposit(const std::string& title,
	const std::string& id,
	float int_rate,
	bool finished,
	Money invested,
	Money planned,
	Money real,
	const TimeDate date_start,
	const TimeDate date_end_planned,
	const TimeDate date_end_real)
	:title(title), id(id), int_rate(int_rate),
	finished(finished),
	invested(invested),
	planned(planned),
	real(real),
	date_start(date_start),
	date_end_planned(date_end_planned),
	date_end_real(date_end_real)
{
	this->id;
}

void ClientDeposit::print_topRow_index() const
{
	using namespace ConsoleFormat;
	
	std::vector<std::string> top_row{
		"Номер",
		"Название",
		"Ставка, %",
		"Вклад, руб",
		"К получению",
		"Начало",
		"Конец"
	};

	ConsoleFormat::PrintRow(top_row, BORDER::BOTTOM);
}

void ClientDeposit::print_TopRow_index() 
{


	using namespace ConsoleFormat;

	std::vector<std::string> top_row{
		"Номер",
		"Название",
		"Ставка, %",
		"Вклад, руб",
		"К получению",
		"Начало",
		"Конец"
	};

	ConsoleFormat::PrintRow(top_row, BORDER::BOTTOM);
}

void ClientDeposit::print_row(const size_t& index) const
{

}

void ClientDeposit::print_row_index(const size_t& index) const
{
	using namespace ConsoleFormat;
	std::vector<std::string> row {
		std::to_string(index),
		title,
		(std::stringstream() << std::fixed << std::setprecision(2) << int_rate).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << invested).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << planned).str(),
		date_start.str_date(),
		date_end_planned.str_date()
	};
	ConsoleFormat::PrintRow(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);


}

void ClientDeposit::print_row_highlight(const size_t& index) const
{

}

void ClientDeposit::print_row_index_highlight(const size_t& index) const
{
	using namespace ConsoleFormat;
	std::vector<std::string> row{
		std::to_string(index),
		title,
		(std::stringstream() << std::fixed << std::setprecision(2) << int_rate).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << invested).str(),
		(std::stringstream() << std::fixed << std::setprecision(2) << planned).str(),
		date_start.str_date(),
		date_end_planned.str_date()
	};
	ConsoleFormat::PrintRow_highlight(row, BORDER::RIGHT | BORDER::LEFT | BORDER::VERTICAL | BORDER::BOTTOM);
}

void ClientDeposit::finish_now()
{
}

bool ClientDeposit::is_finished()
{
	return false;
}

ClientDeposit ClientDeposit::make_from_deposit(const Deposit& deposit, Money invesetment, unsigned days)
{
	Money planned = invesetment * (days / 365.0f) * deposit.int_rate;
	tm current_time = TimeDate::current_time_tm();
	TimeDate current_date = TimeDate(&current_time);
	TimeDate date_planned = TimeDate(&current_time);
	date_planned.add_days(days);
	ClientDeposit cd(deposit.title,
		deposit.id,
		deposit.int_rate,
		false,
		invesetment,
		planned,
		planned,
		current_date,
		date_planned,
		date_planned);

	return cd;
}

Deposit make_deposit(const std::string& title, const float int_rate, const Money min, const Money max)
{
	std::string id = RNG::GenerateNum_str();
	return Deposit(title, id, int_rate, min, max);
}

std::fstream& operator<<(std::fstream& fs, const ClientDeposit& deposit)
{
	fs << deposit.id << ' ';
	fs << deposit.title << ' ';
	fs.write((char*)&deposit.date_start, sizeof(TimeDate));
	fs.write((char*)&deposit.date_end_planned, sizeof(TimeDate));
	fs.write((char*)&deposit.date_end_real, sizeof(TimeDate));
	fs.write((char*)&deposit.invested, sizeof(Money));
	fs.write((char*)&deposit.planned, sizeof(Money));
	fs.write((char*)&deposit.real, sizeof(Money));
	fs.write((char*)&deposit.int_rate, sizeof(float));
	fs.write((char*)&deposit.finished, sizeof(bool));
	return fs;
}

std::fstream& operator>>(std::fstream& fs, ClientDeposit& deposit)
{
	fs >> deposit.id;
	fs >> deposit.title;
	fs.get();
	fs.read((char*)&deposit.date_start, sizeof(TimeDate));
	fs.read((char*)&deposit.date_end_planned, sizeof(TimeDate));
	fs.read((char*)&deposit.date_end_real, sizeof(TimeDate));
	fs.read((char*)&deposit.invested, sizeof(Money));
	fs.read((char*)&deposit.planned, sizeof(Money));
	fs.read((char*)&deposit.real, sizeof(Money));
	fs.read((char*)&deposit.int_rate, sizeof(float));
	fs.read((char*)&deposit.finished, sizeof(bool));
	return fs;
}

ClientDeposit make_client_deposit(std::string title, const Money invested, const float int_rate, const TimeDate date_start, const unsigned days)
{
	TimeDate date_end = date_start;
	date_end.add_days(days);

	TimeDate null;

	Money planned = invested * (365.0f / days) * int_rate;

	std::string id = RNG::GenerateNum_str();

	return ClientDeposit(title, 
		id,
		int_rate, 
		false, 
		invested,
		planned,
		0,
		date_start, 
		date_end,
		null);
}