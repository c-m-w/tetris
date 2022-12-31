/// tetris.cpp

#include "tetris.hpp"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nShowCmd
)
{
#if defined(_DEBUG)
	utils::allocate_console();
#endif

	if (!window::get()->init()
		|| !render_engine::get()->init()
		|| !font_engine::get()->init()
		|| !ui::get()->init()
		|| !game::get()->init())
		return 0;

	auto h = color_t(1.f, 0.f, 0.f, 0.1f).hex();
	auto bmp = font_engine::get()->make_bitmap("agg", 24, color_t(1.f, 0.f, 0.f, 1.f));

	for (auto row : bmp)
	{
		for (auto u : row)
		{
			if ((u & 0xFF000000) > 0x50)
				std::cout << "#";
			else
				std::cout << " ";
		}

		std::cout << std::endl;
	}

	do {
		
		render_engine::get()->begin_scene();

		game::get()->frame();
		/*render_engine::get()->draw_rect({ 0, 0 }, { 30, 30 }, 0x1d94deFF, 0x1670a8C0, 0x1670a8C0, 0x1d94deFF);
		render_engine::get()->draw_rect({ 3, 3 }, { 24, 24 }, 0x1670a8C0, 0x1d94deFF, 0x1d94deFF, 0x1670a8C0);*/

		render_engine::get()->end_scene();
	}
	while (!should_exit);

	return 0;
}
