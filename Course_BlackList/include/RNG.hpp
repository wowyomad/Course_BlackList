#pragma once
#include <string>
#include <iterator>
#include <random>
#include <iomanip>
#include <sstream>
#include <ranges>

#include<unordered_map>


namespace RNG
{
	static std::random_device dev;
	static std::mt19937_64 rng(dev());

	//число длинною в 16 символов
	static const uint64_t MAX = 9'999'999'999'999'999;
	static const uint64_t MIN = 1'000'000'000'000'000;

	template <typename _Ty = uint64_t, size_t len = 16>
	_Ty GenerateNum(size_t min = (std::numeric_limits<_Ty>::min)(), size_t max = MAX)
	{
		std::uniform_int_distribution<_Ty> uid(min, MAX);
		return uid(rng);
	}


	template <typename _Ty = uint64_t, size_t len = 16>
	std::string GenerateNum_str(size_t min = (std::numeric_limits<_Ty>::min)(), size_t max = MAX)
	{
		std::uniform_int_distribution<_Ty> uid(min, max);
		return (std::stringstream() << std::setw(len) << std::setfill('0') << uid(rng)).str();
	}


	template <typename _Ty = uint64_t, std::ranges::range _Arr, size_t len = 16>
	_Ty GenerateNum_withCheck(_Arr usedValues, size_t min = (std::numeric_limits<_Ty>::min)(), size_t max = MAX)
		requires std::random_access_iterator<std::ranges::iterator_t<_Arr>>
	{
		bool generated = false;
		uint64_t num;
		while (!generated)
		{
			num = GenerateNum<_Ty>();
			generated = true;
			for (auto& it : usedValues)
			{
				if (it == num)
				{
					generated = false;
					break;
				}
			}
		}
		return num;
	}

	size_t HashString_withSalt(std::string string, std::string salt)
	{
		return std::hash<std::string>()(string + salt);
	}


	size_t HashString_withSalt(std::string string, size_t salt)
	{
		return std::hash<std::string>()(string + std::to_string(salt));
	}
}
