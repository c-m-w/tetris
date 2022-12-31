/// game.cpp

#include "../tetris.hpp"

void game::callback_up()
{
	game::get()->current_manager->rotate();
}

void game::callback_down()
{
	game::get()->current_manager->move_down();
}

void game::callback_left()
{
	game::get()->current_manager->move_left();
}

void game::callback_right()
{
	game::get()->current_manager->move_right();
}

void game::callback_space()
{
	game::get()->current_manager->drop();
}

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

void game::init_manager()
{
	if (current_manager)
		current_manager.release();

	if (SCREEN_TITLE == screen)
		current_manager = std::make_unique<block_manager>(30, 20, 500);
	else if (SCREEN_GAME == screen)
		current_manager = std::make_unique<block_manager>(10, 20, 350);
	else
		current_manager = nullptr;
}

bool game::init()
{
	screen = SCREEN_TITLE;
	create_screen();
	init_manager();

	window::get()->add_key_callback(callback_up, GLFW_KEY_UP);
	window::get()->add_key_callback(callback_down, GLFW_KEY_DOWN);
	window::get()->add_key_callback(callback_left, GLFW_KEY_LEFT);
	window::get()->add_key_callback(callback_right, GLFW_KEY_RIGHT);
	window::get()->add_key_callback(callback_space, GLFW_KEY_SPACE);

	return true;
}

void game::frame()
{
	if (current_manager)
		current_manager->frame();

	ui::get()->get_body()->draw();
}
