#pragma once

#include <string>

class Password
{
protected:
	std::string hash;
	std::string salt;

public:
	Password(std::string& hash, std::string& salt);
	Password(const Password& other) = default;
	Password(Password&& other) noexcept;
	Password();

	bool operator==(const Password& other) const;

	Password operator=(const Password& other);
	Password operator=(Password&& other);


	friend std::fstream& operator<<(std::fstream& ofs, const Password& obj);
	friend std::fstream& operator>>(std::fstream& ifs, Password& obj);

	friend std::ostream& operator<<(std::ostream& os, const Password& obj);

	bool same_as(std::string input);
};

Password make_password(const std::string& input);
Password make_password(const std::string&& input);