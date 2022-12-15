#pragma once

class Printable
{
public:
	virtual void print_row(const size_t& index) const = 0;
	virtual void print_row_highlight(const size_t& index) const = 0;
	
	virtual void print_topRow_index() const = 0;
	virtual void print_row_index(const size_t& index) const = 0;
	virtual void print_row_index_highlight(const size_t& index) const = 0;
};