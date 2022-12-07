#include "Date.h"
#include <sstream>
#include <iomanip>

bool str_to_tm(const char* str, const char* pattern, tm* datetime)
{
	std::istringstream is(str);
	is >> std::get_time(datetime, pattern);
	if (is.fail())
		return false;
	return true;
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
