/// game.cpp

#include "../tetris.hpp"

void game::create_screen()
{
	auto* const body = ui::get()->get_body();
	
	body->clear();

	switch (screen)
	{
	case SCREEN_TITLE:
	{
		static auto button = ui_types::button("begin game", ui_types::TEXT_REGULAR, { WINDOW_WIDTH / 2, 125 }, [](void*) {std::cout << "CLICKED" << std::endl; });
		static auto title = ui_types::text("tetris", 24, { WINDOW_WIDTH / 2, 40 }, ui_types::bright_white);

		button.set_anchor(ui_types::text::ANCHOR_CENTER);
		title.set_anchor(ui_types::text::ANCHOR_CENTER);
		body->add_child(&button);
		body->add_child(&title);
	}
	break;

	case SCREEN_GAME:
	{

	}
	break;
	}
}

game::game() :
	preview_manager(30, 20, 500),
	game_manager(10, 20, 350)
{ }

bool game::init()
{
	screen = SCREEN_TITLE;
	create_screen();

	return true;
}

void game::frame()
{
	if (screen == SCREEN_TITLE)
		preview_manager.frame();
	else if (screen == SCREEN_GAME)
		game_manager.frame();

	ui::get()->get_body()->draw();
}
