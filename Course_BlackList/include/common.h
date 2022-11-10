#include <string>


namespace common
{
	const char msg_exception[] = "Неизвестное исключение.";
	const char msg_invalid_separtor[] = "Ошибка получения десятичного разделителя.";

	class exception
	{
	protected:
		std::string message;
	public:
		exception(const std::string& info = msg_exception) { message = info; }
		const char* what() const { return message.c_str(); }
	};

	class invalid_separtor :public exception
	{
	public:
		invalid_separtor(const std::string& info = msg_invalid_separtor) : exception(info) {}
	};
}