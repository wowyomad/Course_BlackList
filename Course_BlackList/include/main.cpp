#include <iostream>
#include <string>
#include "common.h"

int main()
{
	std::string str = "ab.ob.a";
	std::cout << std::count(str.begin(), str.end(), '.');
	common::exception ex;
	std::cout << ex.what();
}
