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

	auto u = vector<float, 3>();
	auto v = vector<float, 3>();

	auto w = u + v;

	if (!window::get()->init()
		|| !render_engine::get()->init()
		|| !font_engine::get()->init()
		|| !ui::get()->init()
		|| !game::get()->init())
		return 0;

	do {
		
		render_engine::get()->begin_scene();
		game::get()->frame();
		render_engine::get()->end_scene();

		utils::sleep(1);
	}
	while (!should_exit);

	return 0;
}
