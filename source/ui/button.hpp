/// button.hpp

#pragma once

class button : public i_drawable
{
private:

	std::string text;
	unsigned text_size;
	unsigned padding;
	ui_types::fn_event_callback click_callback;

public:

	button(std::string const& text, unsigned const text_size, location const& position, ui_types::fn_event_callback click_callback) :
		i_drawable(position, {}), text(text), text_size(text_size), padding(text_size * 1.25), click_callback(click_callback)
	{ 
		auto const size = font_engine::get()->get_text_size(text, text_size) + padding * 2 + 2;

		set_size(size);
	}

	void draw() override
	{
		auto const abs = get_absolute_position();

		if (hovered)
			render_engine::get()->draw_rect(abs, size, dark_blue);

		render_engine::get()->draw_text(text, text_size, hovered ? bright_white : white, abs + padding + 1);
		render_engine::get()->draw_rect(abs, size, light_blue, true);
	}
	
	void on_click() override
	{
		click_callback(nullptr);
	}
};
