/// tetris.cpp

#include "tetris.hpp"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nShowCmd
)
{
	coordinate<pixel_t> a(0, 500);
	coordinate<pixel_t> b(500, 500);
	coordinate<pixel_t> c(250, 0);

	primitive d(a.to_relative(), b.to_relative(), c.to_relative());
	primitive_color e(color_t(1.f, 0.f, 0.f), color_t(0.f, 1.f, 0.f), color_t(0.f, 0.f, 1.f));

	if (!render_engine::get()->init())
		return 0;

	do {
		
		render_engine::get()->begin_scene();

		render_engine::get()->draw_primitive(d, e);

		render_engine::get()->end_scene();

	} // Check if the ESC key was pressed or the window was closed
	while (!GetAsyncKeyState(VK_ESCAPE));

	return 0;
}
