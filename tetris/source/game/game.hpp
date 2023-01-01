/// game.hpp

#pragma once

#include "block_manager.hpp"

class game : public i_base<game>
{
public:

	enum SCREEN
	{
		SCREEN_TITLE,
		SCREEN_GAME
	};

private:

	SCREEN screen;
	std::unique_ptr<block_manager> current_manager = nullptr;
	unsigned long long game_time = 0;
	unsigned score = 0;

	/******************************
	*
	* title screen elements
	* 
	******************************/
	static inline ui_types::text* main_title;
	static inline ui_types::button* begin_game;
	static inline ui_types::button* scoreboard;

	/******************************
	*
	* game screen elements
	*
	******************************/
	static inline ui_types::button* back_to_title;
	static inline ui_types::container* game_stats;
	static inline ui_types::text* score_label;
	static inline ui_types::text* score_value;
	static inline ui_types::text* time_label;
	static inline ui_types::text* time_value;

	static void callback_up();
	static void callback_down();
	static void callback_left();
	static void callback_right();
	static void callback_space();

	void create_screen();
	void init_manager();
	
	void update_time();

public:

	game();
	~game();

	bool init() override;

	void frame();
	void navigate(SCREEN to);
};
