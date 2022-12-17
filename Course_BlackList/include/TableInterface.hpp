#pragma once

#include <Windows.h>

#include "console_manip.h"
#include "Printable.h"
#include "PrintFormat.h"

#include "common.h"

#include <vector>
#include <memory>
#include <conio.h>

#include "messages.h"


namespace UI
{
	using namespace message;
	void PrintEnter();
	void PrintEsc();
	void PrintAccept();
	void PrintDecline();

	bool UserAccept();
	void WaitTillEnter();

	void PrintHeader(const msg& name);
	void PrintOption(const msg& option);
	void PrintMessage(const msg& message);
	void PrintString(const msg& message);
	void PrintOption_highlight(const msg& option);
	void PrintLine(const char character = '-');
}


using event = uint8_t;
namespace events
{
	static const event none = 0x00000000;
	static const event select = 0x00000001;
	static const event back = 0x00000002;
	static const event other = 0x00000003;
}

class OptionsInterface
{
	unsigned short pos;
	unsigned short max_pos;
	COORD home;
	event last_event;
	bool to_update;
	std::vector<std::string> options;
	std::string header;

public:
	void update();
	void render();

	event event() const;
	unsigned short position() const;


	OptionsInterface(const std::vector<std::string>& options, COORD home);
	OptionsInterface(const std::vector<std::string>& options, const std::string& header, COORD home);
private:
	void move_up();
	void move_down();

};

template <std::derived_from<Printable> _ItemType>
class TableInterface
{
protected:
	const std::vector<std::shared_ptr<_ItemType>>& origin_ref;
	std::vector<std::pair<size_t, std::shared_ptr<_ItemType>>> items;

	size_t pos;
	size_t size;
	size_t max_pos;

	size_t page;
	size_t max_page;

	COORD home;
	event last_event;
	const size_t rows;

	std::string header;

	bool to_update;

public:
	void update()
	{
		last_event = events::none;
		char input = _getch();

		switch (input)
		{
		case CONSTANT::KEY_ARROW:
			input = _getch();
			switch (input)
			{
			case CONSTANT::KEY_ARROW_UP:
				move_up();
				break;
			case CONSTANT::KEY_ARROW_DOWN:
				move_down();
				break;
			case CONSTANT::KEY_ARROW_LEFT:
				move_left();
				break;
			case CONSTANT::KEY_ARROW_RIGHT:
				move_right();
				break;
			}
			break;

		case CONSTANT::ENTER:
			last_event = events::select;
			break;

		case CONSTANT::ESCAPE:
			last_event = events::back;
			break;
		}
	}
	void render()
	{
		if (to_update)
		{
			//Очистка области консоли. Благодаря этому смена страниц не вызывает мерцающего эффекта
			ClearScreen(home, CONSTANT::CONSOLE_HEIGHT - home.Y);
			to_update = false;
		}

		
		if (!header.empty())
		{
			std::cout << manip::pos(home);
			UI::PrintHeader(header);
		}
		else std::cout << manip::pos(0, 0);



		if (size > (page + 1) * rows)
			max_pos = (page + 1) * rows - 1;
		else
			max_pos = (page * rows) + size % 10 - 1;

		_ItemType::print_TopRow_index();

		for (size_t i = page * rows; i <= max_pos; i++)
		{
			if (i == pos)
				items[i].second->print_row_index_highlight(i + 1);
			else
				items[i].second->print_row_index(i + 1);
		}
		std::cout << manip::pos(0, CONSTANT::CONSOLE_HEIGHT - 4);
		PrintPageCount();
		UI::PrintEnter();
		UI::PrintEsc();

	}
	void refresh()
	{
		size_t i = 0;
		size = origin_ref.size();
		items.resize(size);
		for (const auto& item : origin_ref)
		{
			items[i] = { i, item };
			i++;
		}
		pos = 0;
		page = 0;
		max_page = size / rows;
	}

	size_t index() const
	{
		return items[pos].first;
	}
	event event() const
	{
		return last_event;
	}

	TableInterface(const std::vector<std::shared_ptr<_ItemType>>& origin, const COORD home, const size_t rows)
		: home(home), rows(rows), origin_ref(origin)
	{
		header = "";
		TableInterface::refresh();
	}

	TableInterface(const std::vector<std::shared_ptr<_ItemType>>& origin, const std::string& header, const COORD home, const size_t rows)
		: home(home), rows(rows), origin_ref(origin), header(header)
	{
		TableInterface::refresh();
	}


private:

	void move_left()
	{
		to_update = true;
		if (page > 0)
		{
			page--;
			pos = page * rows;
		}
		else to_update = false;
	}
	void move_right()
	{
		to_update = true;
		if (page < max_page)
		{
			page++;
			pos = page * rows;
		}
		else to_update = false;
	}
	void move_up()
	{
		if (pos > page * rows)
			pos--;
		else if (page > 0)
		{
			page--;
			pos--;
			to_update = true;
		}
		else to_update = false;
	}
	void move_down()
	{
		if (pos < max_pos)
			pos++;
		else if (page < max_page)
		{
			page++;
			pos++;
			to_update = true;
		}
		else to_update = false;
	}

protected:
	void PrintPageCount()
	{
		std::string pages = "Страница " + std::to_string(page + 1) + " из " + std::to_string(max_page + 1);
		UI::PrintString(pages);
	}
};
