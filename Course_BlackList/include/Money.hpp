#pragma once

#include <iostream>
#include <string>
#include "common.h"

#include <sstream>
#include <iomanip>

#include <vector>

template <const char sep = '.'>
class Money_64
{
	uint64_t whole;
	uint64_t fraction;

	enum class SIGN
	{
		positive = '\0',
		negative = '-'
	};

	SIGN sign = SIGN::positive;

public:
	Money_64() : whole(0), fraction(0) { }
	Money_64(const Money_64& other) : whole(other.whole), fraction(other.fraction), sign(other.sign) {}
	Money_64(Money_64&& other) : whole(other.whole), fraction(other.fraction), sign(other.sign) {}
	Money_64(const std::string& value) : whole(0), fraction(0) { *this = value; }
	Money_64(std::string&& value) : whole(0), fraction(0) { *this = std::move(value); }
	Money_64(const int value) : whole(value), fraction(0) {}


	Money_64 operator=(const std::string& value)
	{
		switch (std::count(value.begin(), value.end(), sep))
		{
		case 0:
			whole = atoi(value.c_str());
			break;
		case 1:
		{
			uint64_t sep_pos = value.find(sep);
			if (sep_pos == value.length())
			{
				whole = atoi(value.c_str());
				break;
			}
			whole = atoi(value.substr(0, sep_pos).c_str());

			if (value.length() > sep_pos + 1)
				fraction = 10 * (value[sep_pos + 1] - '0');

			if (value.length() > sep_pos + 2)
				fraction += value[sep_pos + 2] - '0';

			break;
		}
		default:
			throw common::invalid_separtor();
		}
		return *this;
	}
	Money_64 operator=(const Money_64& other) { return *this = Money_64(other); }
	Money_64 operator=(Money_64&& other)
	{
		whole = other.whole;
		fraction = other.fraction;
		sign = other.sign;
		return *this;
	}
	Money_64 operator=(std::string&& value) { return *this = value; }
	Money_64 operator=(double value) { return *this = std::to_string(value); }
	Money_64 operator=(const char* value) { return *this = std::string(value); }

	Money_64 operator+=(const Money_64& other)
	{
		if (sign != other.sign)
		{
			if (sign == SIGN::negative)
			{
				return *this = other - -(*this);
			}
			else
			{
				return *this = *this - -other;
			}
		}

		whole += other.whole;
		fraction += other.fraction;

		if (fraction >= 100)
		{
			whole += 1;
			fraction -= 100;
		}
		return *this;
	}

	Money_64 operator+=(Money_64&& other) { return *this += other; }
	Money_64 operator+=(const std::string& value) { return *this += Money_64(value); }
	Money_64 operator+=(std::string&& value) { return *this += Money_64(value); }
	Money_64 operator+=(const char* value) { return *this += Money_64(std::string(value)); }
	Money_64 operator+=(double value) { return *this += Money_64(std::to_string(value)); }

	Money_64 operator-=(const Money_64& other)
	{
		if (sign != other.sign)
		{
			return *this += -other;
		}

		if (*this < other)
		{
			return *this = -(other - *this);
		}

		fraction += 100 - other.fraction;
		whole -= other.whole;

		if (fraction < 100)
		{
			if (whole >= 1)
			{
				whole -= 1;
			}
			else
			{
				fraction = 100 - fraction;
				this->inverse();
			}
		}
		else
		{
			fraction -= 100;
		}
		/*if (whole == 0 and fraction == 0)
			sign = SIGN::positive;*/
	}
	Money_64 operator-=(Money_64&& other) { return *this -= other; }
	Money_64 operator-=(std::string& value) { return *this -= Money_64(value); }
	Money_64 operator-=(std::string&& value) { return *this -= Money_64(value); }
	Money_64 operator-=(const char* value) { return *this -= Money_64(std::string(value)); }
	Money_64 operator-=(double value) { return *this -= Money_64(std::to_string(value)); }

	Money_64 operator+(const Money_64& other) const
	{
		Money_64 money(*this);
		money += other;
		return money;
	}
	Money_64 operator+(Money_64&& other) const { return *this + other; }
	Money_64 operator+(std::string& value) const { return *this + Money_64(value); }
	Money_64 operator+(std::string&& value) const { return *this + Money_64(value); }
	Money_64 operator+(double value) { return *this + Money_64(std::to_string(value)); }

	Money_64 operator-() const
	{
		Money_64 money(*this);
		money.inverse();
		return money;
	}

	Money_64 operator-(const Money_64& other) const
	{
		Money_64 money(*this);
		money -= other;
		return money;
	}
	Money_64 operator-(Money_64&& other) const { return *this - other; }
	Money_64 operator-(std::string& value) const { return *this - Money_64(value); }
	Money_64 operator-(std::string&& value) const { return *this - Money_64(value); }
	Money_64 operator-(double value) { return *this - Money_64(std::to_string(value)); }

	Money_64 operator*=(double mul)
	{
		if (mul < 0)
		{
			mul = fabs(mul);
			this->inverse();
		}

		double big = whole * mul;
		double rest = (big - uint64_t(big)) * 100;
		fraction = round((fraction * mul + rest));
		whole = big + fraction / 100;
		fraction %= 100;

		return *this;
	}
	Money_64 operator* (double mul)
	{
		return Money_64(*this) *= mul;
	}

	bool operator==(const Money_64& other) const
	{
		return whole == other.whole and fraction == other.fraction;
	}
	bool operator>(const Money_64& other) const
	{
		if (whole == other.whole)
			if (fraction == other.fraction)
				return false;
			else return fraction > other.fraction;
		else return whole > other.whole;
	}
	bool operator>=(const Money_64& other) const
	{
		if (whole == other.whole)
			if (fraction == other.fraction)
				return true;
			else return fraction > other.fraction;
		else return whole > other.whole;
	}
	bool operator<(const Money_64& other) const
	{
		if (whole == other.whole)
			if (fraction == other.fraction)
				return false;
			else return fraction < other.fraction;
		else return whole < other.whole;
	}
	bool operator<=(const Money_64& other) const
	{
		if (whole == other.whole)
			if (fraction == other.fraction)
				return true;
			else return fraction < other.fraction;
		else return whole < other.whole;
	}

	void print() const { std::cout << (char)sign << whole << '.' << std::setw(2) << std::setfill('0') << std::right << fraction; }
	float Float() const { return (float)(whole + fraction / 100.0f); }
	double Double() const { return (double)(whole + fraction / 100.0); }


private:
	void inverse()
	{
		if (whole or fraction)
			sign = sign == SIGN::positive ? SIGN::negative : SIGN::positive;
		else
			sign = SIGN::positive;
	}

};