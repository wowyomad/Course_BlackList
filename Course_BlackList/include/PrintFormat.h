#pragma once

#include <string>
#include <vector>

#include "console_manip.h"
#include "common.h"


namespace ConsoleFormat
{
	namespace BORDER
	{
		const uint8_t TOP = 0b00000001;
		const uint8_t BOTTOM = 0b00000010;
		const uint8_t LEFT = 0b00000100;
		const uint8_t RIGHT = 0b00001000;
		const uint8_t VERTICAL = 0b00010000;
		const uint8_t UNDERSCORE = 0b00100000;
	}

	void PrintCenteredLine(std::string str, std::string format = "", const char fill = ' ', const unsigned width = CONSTANT::CONSOLE_WIDTH);
	void PrintCenteredNewLine(std::string str, std::string format = "", const char fill = ' ', const unsigned width = CONSTANT::CONSOLE_WIDTH);

	std::string CenteredLine(std::string str, std::string format, const char fill = ' ', const unsigned width = CONSTANT::CONSOLE_WIDTH);
	std::string CenteredNewLine(std::string str, std::string format, const char fill = ' ', const unsigned width = CONSTANT::CONSOLE_WIDTH);

	std::string StringBox(std::string str, const unsigned boxWidth = CONSTANT::BOX_WIDTH);

	void PrintRow(const std::vector<std::string>& vectorString,
		const uint8_t borders,
		const int cellWidth = CONSTANT::CELL_WIDTH,
		const int consoleWidth = CONSTANT::CONSOLE_WIDTH);


	void PrintRow_underscore(const std::vector<std::string>& stringVector,
		const uint8_t borders,
		const int cellWidth = CONSTANT::CELL_WIDTH,
		const int consoleWidth = CONSTANT::CONSOLE_WIDTH);


	std::string RowString(const std::vector<std::string>& vectorString,
		const uint8_t borders = BORDER::LEFT | BORDER::RIGHT | BORDER::BOTTOM | BORDER::TOP | BORDER::VERTICAL,
		int row_width = CONSTANT::ROW_WIDTH,
		int console_width = CONSTANT::CONSOLE_WIDTH);

	std::string RowString_highlight(const std::vector<std::string>& vectorString,
		const uint8_t borders,
		int row_width = CONSTANT::ROW_WIDTH,
		int console_width = CONSTANT::CONSOLE_WIDTH);

	size_t offset(size_t console_width, size_t row_width, size_t rows);
}

void ClearScreen(COORD home = { 0, 0 });