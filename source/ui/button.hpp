/// button.hpp

#pragma once

class button : public ui::i_drawable
{
private:

	std::string text;
	unsigned text_size;

public:

	button(std::string const& text, unsigned const text_size, location const& position) :
		i_drawable(position, {}), text(text), text_size(text_size)
	{ }

	void draw() override
	{
		auto const padding = unsigned(text_size * 1.25);
		auto const s = font_engine::get()->get_text_size(text, text_size);

		render_engine::get()->draw_text(text, text_size, white, position + padding + 1);
		render_engine::get()->draw_rect(position, s + padding * 2 + 2, light_blue, true);
	}
};
