/// button.hpp

#pragma once

class button : public i_drawable
{
private:

	std::string text;
	unsigned text_height;
	dimension text_size;
	unsigned padding;
	ui_types::fn_event_callback click_callback;

public:

	button(std::string const& text, unsigned const text_height, location const& position, ui_types::fn_event_callback click_callback) :
		i_drawable(position, {}), text(text), text_height(text_height), padding(text_height * 1.25), click_callback(click_callback)
	{ 
		text_size = font_engine::get()->get_text_size(text, text_height);

		set_size(text_size + padding * 2 + 2);
	}

	void draw() override
	{
		auto const abs = get_absolute_position();
		auto const s = get_size();

		if (hovered)
			render_engine::get()->draw_rect(abs, s, dark_blue);

		render_engine::get()->draw_text(text, text_height, hovered ? bright_white : white, abs + s / 2 - text_size / 2);
		render_engine::get()->draw_rect(abs, s, light_blue, true);
	}
	
	void on_click() override
	{
		click_callback(nullptr);
	}
};
