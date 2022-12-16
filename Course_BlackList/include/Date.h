#pragma once

#include "console_manip.h"

#include <string>


class TimeDate
{
	struct tm time_date;
public:

	TimeDate(const struct tm* tm);
	TimeDate();

	void add_days(size_t days);
	void add_months(size_t months);
	void add_years(size_t years);
	void add_hours(size_t hours);

	void sub_days(size_t days);
	void sub_months(size_t months);
	void sub_years(size_t years);
	void sub_hours(size_t hours);

	std::string str_time() const;
	std::string str_date() const;

	static std::string current_time_str();
	static tm current_time_tm();
	static std::string current_date_str();

};

unsigned short days_in_month(const tm* datetime);
bool is_leap_year(const tm* datetime);
bool str_to_tm(const char* str, const char* pattern, tm* datetime);
bool str_to_tm_leaps(const char* str, const char* pattern, tm* datetime);
