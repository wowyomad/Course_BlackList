#include "PrintFormat.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include <sstream>

#include "console_manip.h"




std::string ConsoleFormat::RowString(const std::vector<std::string>& stringVector,
	const uint8_t borders,
	int row_width,
	int console_width)
{
	if (row_width < 3) row_width = CONSTANT::ROW_WIDTH;
	if (stringVector.size() <= 0)
		throw std::invalid_argument("fdsf");

	unsigned rows = stringVector.size();
	int cellWidth = row_width / rows + (row_width / rows) % 2;
	cellWidth = cellWidth > 2 ? cellWidth : 3;

	unsigned maxLength = [stringVector]()->unsigned
	{
		unsigned maxLength = 0;
		for (const auto& it : stringVector)
		{
			if (it.length() > maxLength)
				maxLength = it.length();
		}
		return maxLength;
	}();

	int offset = ConsoleFormat::offset(console_width, row_width, rows);

	offset = offset > 0 ? offset : 0;
	unsigned lines = maxLength % (cellWidth - 2) == 0 ? 0 : 1;
	lines += maxLength / (cellWidth - 2);
	unsigned line_length = cellWidth - 2;
	unsigned half_line_length = line_length / 2;

	char downBorder = BORDER::BOTTOM & borders ? '_' : ' ';
	char leftBorder = BORDER::LEFT & borders ? '|' : ' ';
	char rightBorder = BORDER::RIGHT & borders ? '|' : ' ';
	char innerSideBorder = BORDER::VERTICAL & borders ? '|' : ' ';

	std::stringstream row_stream;


	if (BORDER::TOP & borders)
	{
		row_stream << std::setw(offset) << std::setfill(' ') << ' ' << ' ';
		for (int i = 0; i < rows; i++)
		{
			row_stream << std::setw(cellWidth - 1) << std::setfill('_') << ' ';
		}
		row_stream << '\n';
	}

	row_stream << std::setw(offset) << std::setfill(' ') << ' ';
	row_stream << leftBorder << std::setw(cellWidth - 1) << std::setfill(' ');
	for (int i = 1; i < rows - 1; i++)
	{
		row_stream << innerSideBorder << std::setw(cellWidth - 1) << std::setfill(' ');
	}
	if (rows > 1)
		row_stream << innerSideBorder;
	row_stream << std::setw(cellWidth - 1) << std::setfill(' ') << rightBorder << '\n';

	unsigned* index = new unsigned[rows] { 0 };
	for (int line = 0; line < lines; line++)
	{
		int m = 0;
		row_stream << std::setw(offset) << std::setfill(' ') << ' ';
		row_stream << leftBorder;
		for (int m = 0; m < rows; m++)

		{
			unsigned first_char_i = index[m];

			unsigned len = (index[m] + line_length) < stringVector[m].length() ? line_length : stringVector[m].length() - first_char_i;

			std::string string_part = stringVector[m].substr(first_char_i);
			string_part = string_part.substr(0, len);

			row_stream << std::setw(half_line_length) << string_part.substr(0, string_part.length() / 2)
				<< string_part.substr(string_part.length() / 2)
				<< std::setw(half_line_length - (string_part.length() - string_part.length() / 2)) << "";

			index[m] = first_char_i + len;

			if (borders & BORDER::UNDERSCORE)
				row_stream << manip::end_underscore;

			if (m == rows - 1)
				row_stream << rightBorder;
			else
				row_stream << innerSideBorder;
		}
		if (BORDER::RIGHT & borders)
			row_stream << "\b \b" << rightBorder;
		row_stream << '\n';
	}
	row_stream << std::setw(offset) << std::setfill(' ') << ' ';
	row_stream << leftBorder << std::setw(cellWidth - 1) << std::setfill(downBorder);

	for (int i = 1; i < rows - 1; i++)
	{
		row_stream << innerSideBorder << std::setw(cellWidth - 1) << std::setfill(downBorder);
	}

	if (rows > 1)
		row_stream << innerSideBorder;
	row_stream << std::setw(cellWidth - 1) << std::setfill(downBorder) << rightBorder << '\n';

	delete[] index;

	return row_stream.str();
}

std::string ConsoleFormat::RowString_highlight(const std::vector<std::string>& stringVector,
	const uint8_t borders,
	int row_width,
	int console_width)
{
	if (row_width < 3) row_width = CONSTANT::ROW_WIDTH;

	unsigned rows = stringVector.size();
	int cellWidth = row_width / rows + (row_width / rows) % 2;
	cellWidth = cellWidth > 2 ? cellWidth : 3;

	unsigned maxLength = [&stringVector]()->unsigned
	{
		unsigned maxLength = 0;
		for (const auto& it : stringVector)
		{
			if (it.length() > maxLength)
				maxLength = it.length();
		}
		return maxLength;
	}();

	int offset = ConsoleFormat::offset(console_width, row_width, rows);

	offset = offset > 0 ? offset : 0;
	unsigned lines = maxLength % (cellWidth - 2) == 0 ? 0 : 1;
	lines += maxLength / (cellWidth - 2);
	unsigned line_length = cellWidth - 2;
	unsigned half_line_length = line_length / 2;

	char downBorder = BORDER::BOTTOM & borders ? '_' : ' ';
	char leftBorder = BORDER::LEFT & borders ? '|' : ' ';
	char rightBorder = BORDER::RIGHT & borders ? '|' : ' ';
	char innerSideBorder = BORDER::VERTICAL & borders ? '|' : ' ';

	std::stringstream row_stream;


	if (BORDER::TOP & borders)
	{
		row_stream << std::setw(offset) << std::setfill(' ') << ' ';
		for (int i = 0; i < rows; i++)
		{
			row_stream << manip::bg_green_bright << std::setw(cellWidth - 1) << std::setfill('_') << ' ';
		}
		row_stream << manip::reset;
		row_stream << '\n';
	}

	row_stream << std::setw(offset) << std::setfill(' ') << ' ';
	row_stream << manip::bg_green_bright;
	row_stream << leftBorder << std::setw(cellWidth - 1) << std::setfill(' ');
	for (int i = 1; i < rows - 1; i++)
	{
		row_stream << innerSideBorder << std::setw(cellWidth - 1) << std::setfill(' ');
	}
	if (rows > 1)
		row_stream << innerSideBorder;
	row_stream << std::setw(cellWidth - 1) << std::setfill(' ') << rightBorder;

	row_stream << manip::reset;
	row_stream << '\n';

	unsigned* index = new unsigned[rows] { 0 };
	for (int line = 0; line < lines; line++)
	{
		int m = 0;
		row_stream << std::setw(offset) << std::setfill(' ') << ' ';

		row_stream << manip::bg_green_bright;
		row_stream << leftBorder;
		for (int m = 0; m < rows; m++)

		{

			if (borders & BORDER::UNDERSCORE)
				row_stream << manip::begin_underscore;

			unsigned first_char_i = index[m];

			unsigned len = (index[m] + line_length) < stringVector[m].length() ? line_length : stringVector[m].length() - first_char_i;

			std::string string_part = stringVector[m].substr(first_char_i);
			string_part = string_part.substr(0, len);

			row_stream << std::setw(half_line_length) << string_part.substr(0, string_part.length() / 2)
				<< string_part.substr(string_part.length() / 2)
				<< std::setw(half_line_length - (string_part.length() - string_part.length() / 2)) << "";

			index[m] = first_char_i + len;


			if (borders & BORDER::UNDERSCORE)
				row_stream << manip::end_underscore;

			if (m == rows - 1)
				row_stream << rightBorder;
			else
				row_stream << innerSideBorder;
		}
		if (BORDER::RIGHT & borders)
			row_stream << "\b \b" << rightBorder;

		row_stream << manip::reset;
		row_stream << '\n';
	}

	row_stream << std::setw(offset) << std::setfill(' ') << ' ';

	row_stream << manip::bg_green_bright;
	row_stream << leftBorder << std::setw(cellWidth - 1) << std::setfill(downBorder);

	for (int i = 1; i < rows - 1; i++)
	{
		row_stream << innerSideBorder << std::setw(cellWidth - 1) << std::setfill(downBorder);
	}

	if (rows > 1)
		row_stream << innerSideBorder;
	row_stream << std::setw(cellWidth - 1) << std::setfill(downBorder) << rightBorder;
	row_stream << manip::reset;
	row_stream << '\n';

	delete[] index;

	return row_stream.str();
}

void ConsoleFormat::PrintRow(const std::vector<std::string>& stringVector,
	const uint8_t borders,
	const int cellWidth,
	const int consoleWidth)
{
	std::cout << ConsoleFormat::RowString(stringVector, borders, cellWidth, consoleWidth);
}

void ConsoleFormat::PrintRow_highlight(const std::vector<std::string>& stringVector,
	const uint8_t borders,
	const int cellWidth,
	const int consoleWidth)
{
	std::cout << ConsoleFormat::RowString_highlight(stringVector, borders, cellWidth, consoleWidth);
}

void ConsoleFormat::PrintCenteredLine(std::string str, std::string format, const char fill, const unsigned int width)
{
	std::cout << CenteredLine(str, format, fill, width);
}

void ConsoleFormat::PrintCenteredNewLine(std::string str, std::string format, const char fill, const unsigned int width)
{
	std::cout << CenteredNewLine(str, format, fill, width);
}

std::string ConsoleFormat::CenteredLine(std::string str, std::string format, const char fill, const unsigned int width)
{
	unsigned offset = width / 2;
	size_t half_length = str.length() - str.length() / 2;
	std::stringstream line_stream;

	line_stream << format;
	line_stream << std::setw(offset) << std::setfill(fill)
		<< str.substr(0, half_length) << str.substr(half_length)
		<< std::setw(offset - str.length() + half_length + 2) << std::setfill(fill) << '\n';
	line_stream << manip::reset;

	//std::string line = line_stream.str();
	//line.insert(0, format);
	//line += manip::reset;

	return line_stream.str();

}

std::string ConsoleFormat::CenteredNewLine(std::string str, std::string format, const char fill, const unsigned int width)
{
	return CenteredLine(str, format, fill, width) + '\n';
}

std::string ConsoleFormat::StringBox(std::string str, unsigned boxWidth)
{
	if (boxWidth < 3) boxWidth = CONSTANT::BOX_WIDTH;

	unsigned middle = CONSTANT::CONSOLE_WIDTH / 2;

	unsigned offset = (middle - boxWidth / 2) + 2;
	size_t half_length = str.length() / 2;
	std::stringstream line_stream;

	//16
	line_stream << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	line_stream << std::setw(offset) << '|' << std::setw(boxWidth - 1) << std::setfill('_') << '|' << '\n';
	line_stream << std::setw(offset) << '|';
	line_stream << std::setw(boxWidth / 2) << str.substr(0, half_length) << str.substr(half_length);
	line_stream << std::setw(offset - str.length() + half_length + 2) << '|' << '\n';
	line_stream << std::setw(offset) << '|' << std::setw(boxWidth - 1) << std::setfill('_') << '|' << '\n';


	return line_stream.str();

}

size_t ConsoleFormat::offset(size_t console_width, size_t row_width, size_t rows)
{
	return (console_width - row_width) / 2 + rows / 2;
}

void ClearScreen(COORD home)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD count;
	FillConsoleOutputCharacter(handle, ' ', cellCount, home, &count);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, cellCount, home, &count);

	SetConsoleCursorPosition(handle, home);
}

void ClearScreen(COORD home, unsigned short line_count)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y - (csbi.dwSize.Y - line_count) * csbi.dwSize.X;

	DWORD count;
	FillConsoleOutputCharacter(handle, ' ', cellCount, home, &count);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, cellCount, home, &count);

	SetConsoleCursorPosition(handle, home);
}

void ClearScreen()
{
	ClearScreen({ 0, 0 });
}