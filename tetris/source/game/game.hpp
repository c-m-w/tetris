/// game.hpp

#pragma once

#include "block_manager.hpp"

class game : public i_base<game>
{
private:

	enum SCREEN
	{
		SCREEN_TITLE,
		SCREEN_GAME
	};

	SCREEN screen;
	std::unique_ptr<block_manager> current_manager = nullptr;

	static void callback_up();
	static void callback_down();
	static void callback_left();
	static void callback_right();
	static void callback_space();

	void create_screen();
	void init_manager();

public:

	bool init() override;

	void frame();
};
