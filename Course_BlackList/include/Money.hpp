#include <iostream>
#include <string>
#include "common.h"

template <const char sep = '.'>
class Money_64
{
	uint64_t whole;
	uint16_t fraction;

public:
	Money_64(std::string num_str)
	{
		if (std::count(num_str.begin(), num_str.end(), sep) != 1)
			throw common::invalid_separtor;
	}
};