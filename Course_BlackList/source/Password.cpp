#include "Password.h"

#include "RNG.hpp"
#include <fstream>


Password make_password(const std::string& input)
{
	std::string salt = RNG::GenerateNum_str();
	std::string hash = RNG::HashString_withSalt(input, salt);
	return Password(hash, salt);
}

Password make_password(const std::string&& input)
{
	return make_password(input);
}

Password::Password(std::string& hash, std::string& salt)
	:hash(hash), salt(salt) {}

Password::Password()
	:hash("none"), salt("none") {}

Password::Password(Password&& other) noexcept
	: hash(std::move(other.hash)),
	salt(std::move(other.salt)) {}


bool Password::operator==(const Password& other) const
{
	return hash == other.hash and salt == other.salt;
}

Password Password::operator=(const Password& other)
{
	this->hash = other.hash;
	this->salt = other.salt;
	return *this;
}

Password Password::operator=(Password&& other)
{
	this->hash = other.hash;
	this->salt = other.salt;
	return *this;
}


bool Password::same_as(std::string input)
{
	return RNG::HashString_withSalt(input, salt) == hash;
}


std::fstream& operator<<(std::fstream& ofs, const Password& obj)
{
	ofs << obj.hash << ' ' << obj.salt;
	return ofs;
}
std::fstream& operator>>(std::fstream& ifs, Password& obj)
{
	ifs >> obj.hash >> obj.salt;
	return ifs;
}
std::ostream& operator<<(std::ostream& os, const Password& obj)
{
	os << "hash\t" << obj.hash << '\n'
		<< "salt\t" << obj.salt;
	return os;
}
