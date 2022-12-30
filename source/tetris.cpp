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

	coordinate<pixel_t> a(0, 0);
	coordinate<pixel_t> b(0, 500);
	coordinate<pixel_t> c(500, 0);

	primitive d(a.to_relative(), b.to_relative(), c.to_relative());
	primitive_color e(color_t(1.f, 0.f, 0.f, 0.5f), color_t(0.f, 1.f, 0.f, 1.f), color_t(0.f, 0.f, 1.f, 0.f));

	if (!render_engine::get()->init()
		|| !font_engine::get()->init())
		return 0;

	auto h = color_t(1.f, 0.f, 0.f, 0.1f).hex();
	auto bmp = font_engine::get()->make_bitmap("agg", 24, color_t(1.f, 0.f, 0.f, 0.5f));

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

	/*for (auto i = 0; i < bmp.height(); i++)
	{
		for (auto j = 0; j < bmp.width(); j++)
		{
			if ((bmp[{i, j}] & 0xFF) > 0)
				std::cout << "#";
			else
				std::cout << " ";
		}

		std::cout << std::endl;
	}*/

	do {
		
		render_engine::get()->begin_scene();

		render_engine::get()->draw_primitive(d, e);
		render_engine::get()->draw_text("test", 6, color_t(1.f, 1.f, 1.f, 0.5f), coordinate<pixel_t>(0, 0));

		render_engine::get()->end_scene();

	}
	while (!GetAsyncKeyState(VK_ESCAPE));

	return 0;
}
