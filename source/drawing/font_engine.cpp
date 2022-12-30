/// font_engine.cpp

#include "../tetris.hpp"

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

unsigned char** font_engine::make_bitmap(std::string const & text, unsigned size)
{
	FT_Set_Char_Size(font, size * 64, 0, 300, 0);
	
	auto const slot = font->glyph;
	FT_Vector pen{};
	static unsigned char bitmap[200][200];
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

		for (auto x1 = slot->bitmap_left, x2 = 0;
			x1 < slot->bitmap_left + slot->bitmap.width;
			x1++, x2++)
		{
			for (auto y1 = 200 - slot->bitmap_top - 8, y2 = 0;
				y1 < 200 - slot->bitmap_top - 8 + slot->bitmap.rows;
				y1++, y2++)
			{
				if (x1 < 0 || x1 > 200
					|| y1 < 0 || y1 > 200)
					continue;

				bitmap[y1][x1] = slot->bitmap.buffer[y2 * slot->bitmap.width + x2];
			}
		}

		pen.x += slot->advance.x;
		pen.y += slot->advance.y;

		previous = slot->glyph_index;
	}

	return reinterpret_cast<unsigned char**>(bitmap);
}
