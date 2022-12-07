#pragma once
#include <fstream>

class Writeable
{
public:
	virtual void SelfWrite(std::ofstream& ofs) const = 0;
};


class Readable
{
public:
	virtual void SelfRead(std::ifstream& ifs) = 0;
};