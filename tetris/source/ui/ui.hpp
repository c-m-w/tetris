/// ui.hpp

#pragma once

class ui;

namespace ui_types
{
	using fn_event_callback = std::function<void(void*)>;

	inline const color_t black = color_t(0x1B2233FF);
	inline const color_t dark_blue = color_t(0x313E5DFF);
	inline const color_t blue = color_t(0x394970FF);
	inline const color_t light_blue = color_t(0x8AB4F8FF);
	inline const color_t white = color_t(0xE0E0E0D0);
	inline const color_t bright_white = color_t(0xFFFFFFFF);
	inline const color_t red = color_t(0xDB1414FF);

	inline constexpr auto TEXT_SMALL = 4u;
	inline constexpr auto TEXT_REGULAR = 6u;
	inline constexpr auto TEXT_LARGE = 12u;

#include "i_drawable.hpp"
#include "container.hpp"
#include "text.hpp"
#include "button.hpp"
}

class ui : public i_base<ui>
{
private:

	ui_types::container body;
	ui_types::i_drawable* hovered_element = nullptr;

	static void mouse_click();
	static void mouse_move(unsigned const x, unsigned const y);
	static ui_types::i_drawable* find_hovered_children(unsigned const x, unsigned const y, ui_types::container* const parent);

public:

	ui();

	bool init() override;
	bool shutdown() override;

	ui_types::container* const get_body();
	bool is_element_hovered(ui_types::i_drawable* const element);
};
