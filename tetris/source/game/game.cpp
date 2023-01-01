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
		main_title->set_anchor(ui_types::text::ANCHOR_CENTER);
		begin_game->set_anchor(ui_types::text::ANCHOR_CENTER);
		scoreboard->set_anchor(ui_types::text::ANCHOR_CENTER);

		body->add_child(main_title);
		body->add_child(begin_game);
		body->add_child(scoreboard);
	}
	break;

	case SCREEN_GAME:
	{
		score_value->set_anchor(ui_types::text::ANCHOR_RIGHT);
		time_value->set_anchor(ui_types::text::ANCHOR_RIGHT);

		body->add_child(back_to_title);
		body->add_child(game_stats);
		game_stats->add_child(score_label);
		game_stats->add_child(score_value);
		game_stats->add_child(time_label);
		game_stats->add_child(time_value);

		game_time = utils::time() / 1000ull;
	}
	break;
	}

	init_manager();
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

void game::update_time()
{
	auto const duration = utils::time() / 1000 - game_time;

	time_value->set_text(std::to_string(duration));
}

game::game()
{
	// todo change these to std::unique_ptr
	/******************************
	*
	* title screen elements
	*
	******************************/
	main_title = new ui_types::text("tetris",
									24,
									{ WINDOW_WIDTH / 2, 40 },
									ui_types::bright_white);
	begin_game = new ui_types::button("begin game",
									  ui_types::TEXT_REGULAR,
									  { WINDOW_WIDTH / 2, 125 },
									  [](void*) { game::get()->navigate(SCREEN_GAME); });
	scoreboard = new ui_types::button("scoreboard",
									  ui_types::TEXT_REGULAR,
									  { WINDOW_WIDTH / 2, 160 },
									  [](void*) { });

	/******************************
	*
	* game screen elements
	*
	******************************/
	back_to_title = new ui_types::button("back",
										 ui_types::TEXT_REGULAR,
										 { 20, 20 },
										 [](void*) { game::get()->navigate(SCREEN_TITLE); });
	game_stats = new ui_types::container({ 750, 10 },
										 { 140, 100 }, 
										 ui_types::container::DRAW_OUTLINE);
	score_label = new ui_types::text("score: ",
							   ui_types::TEXT_REGULAR,
							   { 10, 10 },
							   ui_types::white);
	score_value = new ui_types::text(std::to_string(score),
		ui_types::TEXT_REGULAR,
		{ 120, 10 },
		ui_types::white);
	time_label = new ui_types::text("time: ",
							  ui_types::TEXT_REGULAR,
							  { 10, 30 },
							  ui_types::white);
	time_value = new ui_types::text("0",
		ui_types::TEXT_REGULAR,
		{ 120, 30 },
		ui_types::white);
}

game::~game()
{
	delete main_title;
	delete begin_game;
	delete scoreboard;

	delete back_to_title;
	delete game_stats;
	delete score_label;
	delete score_value;
	delete time_label;
	delete time_value;
}

bool game::init()
{
	screen = SCREEN_TITLE;
	create_screen();

	window::get()->add_key_callback(callback_up, GLFW_KEY_UP);
	window::get()->add_key_callback(callback_down, GLFW_KEY_DOWN);
	window::get()->add_key_callback(callback_left, GLFW_KEY_LEFT);
	window::get()->add_key_callback(callback_right, GLFW_KEY_RIGHT);
	window::get()->add_key_callback(callback_space, GLFW_KEY_SPACE);

	return true;
}

void game::frame()
{
	update_time();

	if (current_manager)
		current_manager->frame();

	ui::get()->get_body()->draw();
}

void game::navigate(SCREEN to)
{
	screen = to;
	create_screen();
}
