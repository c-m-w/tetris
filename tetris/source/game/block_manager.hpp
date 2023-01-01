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
	location grid_offset;
	block_t current;
	std::vector<std::vector<square_t>> squares;
	std::function<void(void)> clear_row_callback;

	void new_block()
	{
		current.block_type = static_cast<BLOCK_TYPE>(utils::random_number(BLOCK_NONE + 1, BLOCK_MAX - 1));
		current.relative_blocks = block_relative_locations[current.block_type];
	
		auto x_extension = 0;

		for (auto const& block : current.relative_blocks)
			x_extension = std::max(x_extension, static_cast<int>(block[0]));

		current.position = { utils::random_number(0, static_cast<int>(nx) - x_extension - 1), 0 };
	}

	bool obstructed_down()
	{
		for (auto const block : current.relative_blocks)
			if (auto const abs = current.position + block;
				abs[1] == ny - 1
				|| squares[abs[0]][abs[1] + 1].parent_block != BLOCK_NONE)
				return true;

		return false;
	}

	bool obstructed_left()
	{
		for (auto const block : current.relative_blocks)
			if (auto const abs = current.position + block;
				abs[0] == 0
				|| squares[abs[0] - 1][abs[1]].parent_block != BLOCK_NONE)
				return true;

		return false;
	}

	bool obstructed_right()
	{
		for (auto const block : current.relative_blocks)
			if (auto const abs = current.position + block;
				abs[0] == nx - 1
				|| squares[abs[0] + 1][abs[1]].parent_block != BLOCK_NONE)
				return true;

		return false;
	}

	void shift_rows_down(unsigned const start_y)
	{
		for (int y = start_y; y >= 0; y--)
			for (auto x = 0u; x < nx; x++)
				squares[x][y + 1] = squares[x][y];
	}

	void clear_rows()
	{
		for (int y = ny - 1; y >= 0; y--)
		{
			auto row_filled = true;

			for (auto x = 0u; x < nx && row_filled; x++)
				row_filled &= BLOCK_NONE != squares[x][y].parent_block;

			if (row_filled)
			{
				shift_rows_down(y - 1);
				clear_row_callback();
			}
		}
	}

	void cement_block()
	{
		for (auto const& block : current.relative_blocks)
		{
			auto const abs = current.position + block;

			squares[abs[0]][abs[1]].parent_block = current.block_type;
		}

		current.block_type = BLOCK_NONE;
		clear_rows();
	}

	void move()
	{
		if (auto const time = utils::time(); time - last_fall_time >= fall_time)
		{
			if (obstructed_down())
				cement_block();
			else
				current.position[1] += 1;

			last_fall_time = time;
		}
	}

	bool block_occluded()
	{

		for (auto const& block : current.relative_blocks)
		{
			auto const abs = current.position + block;

			if (BLOCK_NONE != squares[abs[0]][abs[1]].parent_block)
				return true;
		}

		return false;
	}

	void draw_square(BLOCK_TYPE const type, location const & position)
	{
		if (type == BLOCK_NONE)
			return;

		auto const screen_position = position * BLOCK_SIZE;
		auto const& light = block_light_colors[type];
		auto const& dark = block_dark_colors[type];

		render_engine::get()->draw_rect(grid_offset + screen_position,
										{ BLOCK_SIZE, BLOCK_SIZE }, 
										light, dark, dark, light);
		render_engine::get()->draw_rect(grid_offset + screen_position + BLOCK_BORDER,
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

	void draw_outline()
	{
		render_engine::get()->draw_rect(grid_offset - 2, { nx * BLOCK_SIZE + 4, ny * BLOCK_SIZE + 4}, ui_types::blue, true);
	}

public:

	block_manager(unsigned const nx, unsigned const ny, unsigned long long const fall_time, std::function<void(void)> clear_row_callback) :
		nx(nx), ny(ny), fall_time(fall_time), last_fall_time(utils::time()), clear_row_callback(clear_row_callback)
	{
		auto const grid_width = nx * BLOCK_SIZE;

		grid_offset = { WINDOW_WIDTH / 2 - grid_width / 2, 0 };

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
		draw_outline();
	}

	void rotate()
	{
		enum
		{
			VALID,
			SMALL_X,
			LARGE_X,
			SMALL_Y,
			LARGE_Y
		};

		auto const invalid_blocks = [this](std::vector<location> const& blocks, const location & position)
		{
			for (auto const& block : blocks)
			{
				if (block[0] + position[0]< 0)
					return SMALL_X;
				else if (block[0] + position[0] >= nx)
					return LARGE_X;
				else if (block[1] + position[1] < 0)
					return SMALL_Y;
				else if (block[1] + position[1] >= ny)
					return LARGE_Y;
			}

			return VALID;
		};

		auto const angle = std::asin(1.0);

		std::vector<location> new_blocks;

		for (auto const& block : current.relative_blocks)
			new_blocks.emplace_back(block.rotate2d(angle, true));

		for (auto result = invalid_blocks(new_blocks, current.position);
			result != VALID;
			result = invalid_blocks(new_blocks, current.position))
			for (auto& block : new_blocks)
				block[result == SMALL_X || result == LARGE_X ? 0 : 1] += result == LARGE_X || result == LARGE_Y ? -1 : 1;

		auto const old_block_copy = current.relative_blocks;

		current.relative_blocks = new_blocks;

		if (block_occluded())
			current.relative_blocks = old_block_copy;
	}

	void move_down()
	{
		if (obstructed_down())
			return;

		current.position[1] += 1;
	}

	void move_left()
	{
		if (obstructed_left())
			return;

		current.position[0] -= 1;
	}

	void move_right()
	{
		if (obstructed_right())
			return;

		current.position[0] += 1;
	}

	void drop()
	{
		while (!obstructed_down())
			current.position[1] += 1;

		cement_block();
	}
};
