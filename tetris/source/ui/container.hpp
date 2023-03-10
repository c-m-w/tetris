/// container.hpp

#pragma once

class container : public i_drawable
{
public:

	enum DRAW_MODE
	{
		DRAW_NONE,
		DRAW_FILL,
		DRAW_OUTLINE
	};

private:

	std::vector<i_drawable*> children { };
	DRAW_MODE draw_mode = DRAW_NONE;

public:

	container(coordinate<pixel_t> const& position, dimension const& size, DRAW_MODE const draw_mode):
		i_drawable(position, size, DRAWABLE_CONTAINER), draw_mode(draw_mode)
	{ }

	void add_child(i_drawable* child)
	{
		children.emplace_back(child);
		child->set_parent(this);
	}

	void clear()
	{
		children.clear();
	}

	void draw() override
	{
		auto const abs = get_absolute_position();
		auto const s = get_size();

		switch (draw_mode)
		{
		case DRAW_FILL:

			render_engine::get()->draw_rect(abs, s, dark_blue);
			break;

		case DRAW_OUTLINE:

			render_engine::get()->draw_rect(abs, s, light_blue, true);
			break;

		default:

			break;
		}

		for (auto const& child : children)
			child->draw();
	}

	friend class ::ui;
};
