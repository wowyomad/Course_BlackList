#include <string>

struct Password
{
	std::string hash;
	std::string salt;
};

class Account
{
	enum class Access
	{
		Denied = -1,
		Pendig,
		Approved
	};
	enum class Level
	{
		User,
		Admin,
		Super
	};

	std::string id;
	Password password;


public:
};