/// font_engine.hpp

#pragma once

class font_engine : public i_base<font_engine>
{
private:

	constexpr static auto FONT_PATH = R"(C:\Users\cole\source\repos\tetris\Debug\VT323-Regular.ttf)";

	FT_Library lib;
	FT_Face font;

public:

	bool init() override;
	bool shutdown() override;

	bitmap make_bitmap(std::string const& text, unsigned size, color_t const& color);
	location get_text_size(std::string const& text, unsigned size);
};
