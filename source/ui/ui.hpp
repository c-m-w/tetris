/// ui.hpp

#pragma once

namespace ui
{
	inline const color_t black = color_t(0x1B2233FF);
	inline const color_t dark_blue = color_t(0x313E5DFF);
	inline const color_t blue = color_t(0x394970FF);
	inline const color_t light_blue = color_t(0x8AB4F8FF);
	inline const color_t white = color_t(0xE0E0E0FF);
	inline const color_t bright_white = color_t(0xFFFFFFFF);
	inline const color_t red = color_t(0xDB1414FF);

	inline constexpr auto TEXT_SMALL = 4u;
	inline constexpr auto TEXT_REGULAR = 6u;
	inline constexpr auto TEXT_LARGE = 12u;

#include "i_drawable.hpp"
#include "container.hpp"
#include "button.hpp"

	inline container* get_body()
	{
		static auto body = container({ 0, 0 }, { WINDOW_WIDTH, WINDOW_HEIGHT }, container::DRAW_NONE);

		return &body;
	}
}
