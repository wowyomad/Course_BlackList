#include "Date.h"
#include <sstream>
#include <iomanip>

#include <ctime>

unsigned short days_in_month(const tm* datetime)
{
	unsigned year = datetime->tm_year + 1900;
	unsigned max_day;
	switch (datetime->tm_mon)
	{
		//февраль
	case 1:
		if (is_leap_year(datetime))	max_day = 29;
		else max_day = 28;
		break;
		//апрель, июнь, сент¤брь, но¤брь
	case 3: case 5: case 8: case 10:
		max_day = 30;
		break;
		//остальные мес¤цы
	default:
		max_day = 31;
		break;
	}
	return max_day;
}

bool is_leap_year(const tm* datetime)
{
	bool is_leap;
	unsigned year = datetime->tm_year;
	if (year % 400 == 0)
		is_leap = true;
	else if (year % 100 == 0)
		is_leap = false;
	else if (year % 4 == 0)
		is_leap = true;
	else
		is_leap = false;

	return is_leap;
}

bool str_to_tm(const char* str, const char* pattern, tm* datetime)
{
	std::istringstream is(str);
	is >> std::get_time(datetime, pattern);

	return !is.fail();
}

bool str_to_tm_leaps(const char* str, const char* pattern, tm* datetime)
{
	if (!str_to_tm(str, pattern, datetime))
		return false;

	unsigned short max_day;
	unsigned year = datetime->tm_year + 1900;

	switch (datetime->tm_mon)
	{
		//февраль
	case 1:
		if (year % 400 == 0)
			max_day = 29;
		else if (year % 100 == 0)
			max_day = 28;
		else if (year % 4 == 0)
			max_day = 29;
		else
			max_day = 28;
		break;
		//апрель, июнь, сент¤брь, но¤брь
	case 3: case 5: case 8: case 10:
		max_day = 30;
		break;
		//остальные мес¤цы
	default:
		max_day = 31;
		break;
	}
	if (datetime->tm_mday <= max_day)
		return true;
	return false;
}

TimeDate::TimeDate(const tm* tm)
{
	if (tm)
	{
		time_date.tm_year = tm->tm_year >= 0 ? tm->tm_year : 0;
		time_date.tm_mon = tm->tm_mon >= 0 ? tm->tm_mon : 0;
		time_date.tm_mday = tm->tm_mday >= 0 ? tm->tm_mday : 0;
		time_date.tm_hour = tm->tm_hour >= 0 ? tm->tm_hour : 0;
		time_date.tm_min = tm->tm_min >= 0 ? tm->tm_min : 0;
		time_date.tm_sec = tm->tm_sec >= 0 ? tm->tm_sec : 0;
	}
	else this->time_date = current_time_tm();
}

TimeDate::TimeDate()
{
	this->time_date = { 0 };
}

void TimeDate::add_days(size_t days)
{
	const size_t ONE_DAY = 24 * 60 * 60;

	time_t raw_time = mktime(&time_date) + days * ONE_DAY;
	
	localtime_s(&time_date, &raw_time);
}

void TimeDate::add_months(size_t months)
{
	unsigned new_months = time_date.tm_mon + months;
	time_date.tm_year += new_months / 12;
	time_date.tm_mon = new_months % 12;
	if (!is_leap_year(&time_date))
		if (time_date.tm_mday > days_in_month(&time_date))
			if (time_date.tm_mon < 11)
			{
				if (time_date.tm_mon == 1) { time_date.tm_mon++; time_date.tm_mday = 1; }
				else time_date.tm_mon++;
			}
			else { time_date.tm_mon = 0; time_date.tm_mday = 1; time_date.tm_year++; }

}

void TimeDate::add_years(size_t years)
{
	const size_t ONE_DAY = 24 * 60 * 60;
	time_date.tm_year += years;
	if (is_leap_year(&time_date))
		if (29 == days_in_month(&time_date))
			if (time_date.tm_mon == 1)
				time_date.tm_mon++;
}

void TimeDate::add_hours(size_t hours)
{
	unsigned new_hours = time_date.tm_hour + hours;
	unsigned days_to_add = (time_date.tm_hour + hours) / 24;
	if (days_to_add > 0)
		add_days(days_to_add);
	time_date.tm_hour = new_hours % 24;
}

void TimeDate::sub_days(size_t days)
{
	throw "не работает!";
}

void TimeDate::sub_months(size_t months)
{
	throw "не работает!";
}

void TimeDate::sub_years(size_t years)
{
	throw "не работает!";
}

void TimeDate::sub_hours(size_t hours)
{
	throw "не работает!";
}

std::string TimeDate::str_date() const
{
	return (std::stringstream() << std::put_time(&time_date, "%d.%m.%Y")).str();
}
std::string TimeDate::str_time() const
{
	return (std::stringstream() << std::put_time(&time_date, "%S:%M:%H")).str();
}

std::string TimeDate::current_time_str()
{
	const char format[] = "%H:%M:%s";
	struct tm current_time = current_time_tm();
	return (std::stringstream() << std::put_time(&current_time, format)).str().c_str();
}

tm TimeDate::current_time_tm()
{
	struct tm current_time;
	time_t raw_time = std::time(nullptr);
	localtime_s(&current_time, &raw_time);
	return current_time;
}

std::string TimeDate::current_date_str()
{
	const char format[] = "%d.%m.%Y";
	struct tm current_time = current_time_tm();
	return (std::stringstream() << std::put_time(&current_time, format)).str().c_str();
}
