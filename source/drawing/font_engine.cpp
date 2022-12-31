/// font_engine.cpp

#include "../tetris.hpp"
#include "font_engine.hpp"

bool font_engine::init()
{
	if (auto const error = FT_Init_FreeType(&lib))
	{
		// todo handle error
		return false;
	}
	auto p = utils::current_path();
	if (auto const error = FT_New_Face(lib,
									   FONT_PATH,
									   0,
									   &font))
	{
		// todo handle error
		return false;
	}

	return true;
}

bool font_engine::shutdown()
{
	return true;
}

bitmap font_engine::make_bitmap(std::string const & text, unsigned size, color_t const & color)
{
	FT_Set_Char_Size(font, size * 64, 0, 300, 0);
	
	auto const hex = color.hex();
	auto const slot = font->glyph;
	FT_Vector pen{};
	auto bmp = bitmap(WINDOW_HEIGHT, WINDOW_WIDTH);
	unsigned char previous = 0;

	for (auto c : text)
	{
		FT_Set_Transform(font, nullptr, &pen);

		if (auto const error = FT_Load_Char(font, c, FT_LOAD_RENDER))
			continue;

		if (previous)
		{
			FT_Vector kerning;

			FT_Get_Kerning(font, previous, slot->glyph_index, FT_KERNING_DEFAULT, &kerning);

			pen.x += kerning.x >> 6;
		}

		for (auto x1 = static_cast<unsigned>(slot->bitmap_left), x2 = 0u;
			x1 < slot->bitmap_left + slot->bitmap.width;
			x1++, x2++)
		{
			for (auto y1 = bmp.height() - slot->bitmap_top - size, y2 = 0u;
				y1 < bmp.height() - slot->bitmap_top - size + slot->bitmap.rows;
				y1++, y2++)
			{
				if (x1 < 0 || x1 > WINDOW_WIDTH
					|| y1 < 0 || y1 > WINDOW_HEIGHT)
					continue;

				bmp[{y1, x1}] = hex & 0x00FFFFFF | ((((hex & 0xFF000000) >> 24) * slot->bitmap.buffer[y2 * slot->bitmap.width + x2]) / 0xFF) << 24;
			}
		}

		pen.x += slot->advance.x;
		pen.y += slot->advance.y;

		previous = slot->glyph_index;
	}

	return bmp.clip();
}

location font_engine::get_text_size(std::string const& text, unsigned size)
{
	auto bmp = make_bitmap(text, size, color_t(0xFFFFFFFF));

	return { bmp.width(), bmp.height() };
}
