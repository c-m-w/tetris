/// container.hpp

#pragma once

class container : public ui::i_drawable
{
public:

	enum DRAW_MODE
	{
		DRAW_NONE,
		DRAW_FILL,
		DRAW_OUTLINE
	};

private:

	std::vector<i_drawable*> children;
	DRAW_MODE draw_mode = DRAW_NONE;

public:

	container(coordinate<pixel_t> const& position, dimension const& size, DRAW_MODE const draw_mode):
		i_drawable(position, size), draw_mode(draw_mode)
	{ }

	void add_child(i_drawable* child)
	{
		children.emplace_back(child);
		child->set_parent(this);
	}

	void draw() override
	{
		auto const abs = get_absolute_position();

		switch (draw_mode)
		{
		case DRAW_FILL:

			render_engine::get()->draw_rect(position[0], position[1], dark_blue);
			break;

		case DRAW_OUTLINE:

			render_engine::get()->draw_rect(position[0], position[1], light_blue, true);
			break;

		default:

			break;
		}

		for (auto const& child : children)
			child->draw();
	}
};
