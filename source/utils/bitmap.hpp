/// bitmap.hpp

#pragma once

class bitmap
{
private:

	unsigned rows, columns;
	std::unique_ptr<unsigned[]> data;

	bool column_empty(unsigned col)
	{
		for (auto y = 0u; y < rows; y++)
			if (data.get()[y * columns + col] & 0xFF)
				return false;

		return true;
	}

	bool row_empty(unsigned row)
	{
		for (auto x = 0u; x < columns; x++)
			if (data.get()[row * columns + x] & 0xFF)
				return false;

		return true;
	}

	unsigned top_padding()
	{
		auto y = 0;

		while (row_empty(y))
			y++;

		return y;
	}

	unsigned left_padding()
	{
		auto x = 0;

		while (column_empty(x))
			x++;

		return x;
	}

	unsigned bottom_padding()
	{
		auto y = 0;

		while (row_empty(rows - y - 1))
			y++;
		
		return y;
	}

	unsigned right_padding()
	{
		auto x = 0;

		while (column_empty(columns - x - 1))
			x++;

		return x;
	}

public:

	class column_iterator
	{
	private:

		unsigned width;
		unsigned* data;
		unsigned i;

	public:

		column_iterator(unsigned const width,
						unsigned* const data,
						unsigned const i = 0) :
						width(width), data(data), i(i)
		{ }

		unsigned* begin()
		{
			return data;
		}

		unsigned* end()
		{
			return data + width;
		}

		column_iterator& operator++()
		{
			i++;
			return *this;
		}

		bool operator==(column_iterator rhs)
		{
			return i == rhs.i;
		}

		bool operator!=(column_iterator rhs)
		{
			return i != rhs.i;
		}

		unsigned operator*()
		{
			return data[i];
		}
	};

	class row_iterator
	{
	private:

		unsigned width, height;
		unsigned* data;
		unsigned i;

	public:

		row_iterator(unsigned const width,
					 unsigned const height,
					 unsigned* const data,
					 unsigned i = 0) :
			width(width), height(height), data(data), i(i)
		{ }

		column_iterator begin()
		{
			return column_iterator(width, data);
		}

		column_iterator end()
		{
			return column_iterator(width, data + height* width);
		}

		row_iterator& operator++()
		{
			i++;
			return *this;
		}

		bool operator==(row_iterator rhs)
		{
			return i == rhs.i;
		}

		bool operator!=(row_iterator rhs)
		{
			return i != rhs.i;
		}

		column_iterator operator*()
		{
			return column_iterator(width, data + i * width);
		}
	};

	bitmap(unsigned r, unsigned c):
		rows(r), columns(c)
	{
		data = std::make_unique<unsigned[]>(r * c);
	}

	bitmap crop(unsigned const y,
				unsigned const x,
				unsigned const rows,
				unsigned const columns)
	{
		auto result = bitmap(rows, columns);

		for (auto i = 0; i < rows; i++)
			for (auto j = 0; j < columns; j++)
				result.data.get()[i * columns + j] = data.get()[(i + y) * this->columns + j + x];

		return result;
	}

	bitmap format()
	{
		auto const new_height = unsigned(pow(2, ceil(log2(height()))));
		auto const new_width = unsigned(pow(2, ceil(log2(width()))));
		auto result = bitmap(new_height, new_width);

		for (auto i = 0; i < rows; i++)
			for (auto j = 0; j < columns; j++)
				result.data.get()[i * result.width() + j] = data.get()[i* columns + j];

		return result;
	}

	bitmap clip()
	{
		auto const y = top_padding(),
			x = left_padding();

		return crop(y,
			x,
			rows - bottom_padding() - y,
			columns - right_padding() - x);
	}

	unsigned height() const
	{
		return rows;
	}

	unsigned width() const
	{
		return columns;
	}

	unsigned* pixels() const
	{
		return data.get();
	}

	unsigned& operator[](unsigned i)
	{
		return data.get()[i];
	}

	unsigned& operator[](std::pair<unsigned, unsigned> c)
	{
		return data.get()[c.first * columns + c.second];
	}

	unsigned operator[](unsigned i) const
	{
		return data.get()[i];
	}

	unsigned operator[](std::pair<unsigned, unsigned> c) const
	{
		return data.get()[c.first * columns + c.second];
	}

	row_iterator begin()
	{
		return row_iterator(columns, rows, data.get());
	}

	row_iterator end()
	{
		return row_iterator(columns, rows, data.get(), rows);
	}
};
