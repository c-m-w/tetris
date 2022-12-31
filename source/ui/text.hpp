/// text.hpp

#pragma once

class text : public i_drawable
{
private:

	std::string t;
	unsigned text_size;
	color_t color;

public:

	text(std::string const& t, unsigned const text_size, location const& position, const color_t& color) :
		i_drawable(position, {}), t(t), text_size(text_size), color(color)
	{
		auto const size = font_engine::get()->get_text_size(t, text_size);

		set_size(size);
	}

	void draw() override
	{
		render_engine::get()->draw_text(t, text_size, color, get_absolute_position());
	}
};