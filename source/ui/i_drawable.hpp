/// i_drawable.hpp

#pragma once

class i_drawable
{
protected:

	i_drawable* parent = nullptr;
	location position = {};
	dimension size = {};
	bool hovered = false;

	coordinate<pixel_t> get_absolute_position()
	{
		auto p = parent;
		auto abs = position;

		while (nullptr != p)
		{
			abs += p->position;

			p = p->parent;
		}

		return abs;
	}

public:

	i_drawable(location const& position, dimension const& size) :
		parent(parent), position(position), size(size)
	{ }

	virtual void draw() = 0;

	void set_parent(i_drawable* const new_parent)
	{
		parent = new_parent;
	}

	friend class container;
};
