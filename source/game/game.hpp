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
	block_manager preview_manager;
	block_manager game_manager;

	void create_screen();

public:

	game();

	bool init() override;

	void frame();
};
