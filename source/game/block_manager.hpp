/// block_manager.hpp

#pragma once

class block_manager
{
public:

	enum BLOCK_TYPE
	{
		BLOCK_NONE,
		BLOCK_SQUARE,
		BLOCK_STICK,
		BLOCK_RANGLE,
		BLOCK_LANGLE,
		BLOCK_PYRAMID,
		BLOCK_MAX
	};

	struct square_t
	{
		BLOCK_TYPE parent_block = BLOCK_NONE;
	};

	struct block_t
	{
		location position;
		std::vector<location> relative_blocks;
		BLOCK_TYPE block_type = BLOCK_NONE;
	};

	inline static const std::vector<location> block_relative_locations[BLOCK_MAX]
	{
		{},
		/*
		*
		*	[][]
		*	[][]
		*
		*/
		{{0, 0}, {1, 0}, {0, 1}, {1, 1}},
		/*
		*
		*	[]
		*	[]
		*	[]
		*	[]
		*
		*/
		{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
		/*
		*
		*	    []
		*	[][][]
		*
		*/
		{{0, 1}, {1, 1}, {2, 1}, {2, 0}},
		/*
		*
		*	[]
		*	[][][]
		*
		*/
		{{0, 0}, {0, 1}, {1, 1}, {2, 1}},
		/*
		*
		*	  []
		*	[][][]
		*
		*/
		{{1, 0}, {0, 1}, {1, 1}, {2, 1}}
	};

	inline static const color_t block_light_colors[BLOCK_MAX]
	{
		0x00000000,
		0xF72F20FF,
		0x1D94DEFF,
		0xD49126FF,
		0x34C41DFF,
		0xD6D620FF
	};

	inline static const color_t block_dark_colors[BLOCK_MAX]
	{
		0x00000000,
		0x9E1E15C0,
		0x1670A8C0,
		0xB07820C0,
		0x278C16C0,
		0xA6A617C0
	};

private:

	static constexpr auto BLOCK_SIZE = 30;
	static constexpr auto BLOCK_BORDER = 3;
	unsigned const nx, ny;
	unsigned long long const fall_time;
	unsigned long long last_fall_time;
	block_t current;
	std::vector<std::vector<square_t>> squares;

	void new_block()
	{
		current.block_type = static_cast<BLOCK_TYPE>(utils::random_number(BLOCK_NONE + 1, BLOCK_MAX - 1));
		current.relative_blocks = block_relative_locations[current.block_type];
	
		auto x_extension = 0;

		for (auto const& block : current.relative_blocks)
			x_extension = std::max(x_extension, static_cast<int>(block[0]));

		current.position = { utils::random_number(0, static_cast<int>(nx) - x_extension - 1), 0 };
	}

	bool obstructed()
	{
		for (auto const block : current.relative_blocks)
			if (auto const abs = current.position + block;
				abs[1] == ny - 1
				|| squares[abs[0]][abs[1] + 1].parent_block != BLOCK_NONE)
				return true;

		return false;
	}

	void move()
	{
		if (auto const time = utils::time(); time - last_fall_time >= fall_time)
		{
			if (obstructed())
			{
				for (auto const & block : current.relative_blocks)
				{
					auto const abs = current.position + block;

					squares[abs[0]][abs[1]].parent_block = current.block_type;
				}

				current.block_type = BLOCK_NONE;
			}
			else
			{
				for (auto& block : current.relative_blocks)
				{
					block[1] += 1;
				}
			}

			last_fall_time = time;
		}
	}

	void draw_square(BLOCK_TYPE const type, location const & position)
	{
		if (type == BLOCK_NONE)
			return;

		auto const screen_position = position * BLOCK_SIZE;
		auto const& light = block_light_colors[type];
		auto const& dark = block_dark_colors[type];

		render_engine::get()->draw_rect(screen_position, 
										{ BLOCK_SIZE, BLOCK_SIZE }, 
										light, dark, dark, light);
		render_engine::get()->draw_rect(screen_position + BLOCK_BORDER, 
										{ BLOCK_SIZE - BLOCK_BORDER * 2, BLOCK_SIZE - BLOCK_BORDER * 2 }, 
										dark, light, light, dark);
	}

	void draw_squares()
	{
		for (auto i = 0u; i < squares.size(); i++)
			for (auto j = 0u; j < squares[i].size(); j++)
			{
				auto const& square = squares[i][j];

				draw_square(square.parent_block, { i, j });
			}

		for (const auto& block : current.relative_blocks)
			draw_square(current.block_type, current.position + block);
	}

public:

	block_manager(unsigned const nx, unsigned const ny, unsigned long long const fall_time) :
		nx(nx), ny(ny), fall_time(fall_time)
	{
		squares.resize(nx);

		for (auto& row : squares)
			row.resize(ny);
	}

	void frame()
	{
		if (BLOCK_NONE == current.block_type)
			new_block();
		else
			move();

		draw_squares();
	}
};
