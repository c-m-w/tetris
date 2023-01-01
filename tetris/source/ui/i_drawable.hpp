/// i_drawable.hpp

#pragma once

class i_drawable
{
public:

	enum DRAWABLE_TYPE
	{
		DRAWABLE_CONTAINER,
		DRAWABLE_INTERACTABLE
	};

	enum ANCHOR_TYPE
	{
		ANCHOR_LEFT,
		ANCHOR_CENTER,
		ANCHOR_RIGHT
	};

protected:

	i_drawable* parent = nullptr;
	location position = {};
	dimension size = {};
	pixel_t w_fixed = 0;
	DRAWABLE_TYPE type;
	ANCHOR_TYPE anchor = ANCHOR_LEFT;
	bool hovered = false;

	location get_absolute_position()
	{
		auto p = parent;
		auto abs = get_anchor_position();

		while (nullptr != p)
		{
			abs += p->get_anchor_position();

			p = p->parent;
		}

		return abs;
	}

	void set_size(dimension const & s)
	{
		size = s;
	}

	dimension get_size()
	{
		if (0 != w_fixed)
			return { w_fixed, size[1] };

		return size;
	}

	location get_anchor_position()
	{
		switch (anchor)
		{
		case ANCHOR_CENTER:

			return { position[0] - get_size()[0] / 2, position[1] };

		case ANCHOR_RIGHT:

			return { position[0] - get_size()[0], position[1] };

		default:

			return position;
		}
	}

public:

	i_drawable(location const& position, dimension const& size, DRAWABLE_TYPE type = DRAWABLE_INTERACTABLE) :
		parent(parent), position(position), size(size), type(type)
	{ }

	virtual void draw() = 0;
	virtual void on_click() { }

	void set_parent(i_drawable* const new_parent)
	{
		parent = new_parent;
	}

	bool is_type(DRAWABLE_TYPE const t)
	{
		return type == t;
	}

	bool contains_point(unsigned const x, unsigned const y)
	{
		auto const abs = get_absolute_position();

		return x >= abs[0] && x <= abs[0] + size[0]
			&& y >= abs[1] && y <= abs[1] + size[1];
	}

	void set_anchor(ANCHOR_TYPE const a)
	{
		anchor = a;
	}

	void fix_width(pixel_t const w)
	{
		w_fixed = w;
	}

	friend class container;
	friend class ::ui;
};
