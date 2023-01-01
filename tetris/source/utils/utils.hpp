/// utils.hpp

#pragma once

#include "types.hpp"

namespace utils
{
	inline void allocate_console()
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}

	inline moment_t time()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	inline void sleep(unsigned long long ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	template<typename T>
	T random_number(T const min, T const max);

	template<>
	int random_number<int>(int const min, int const max);

	template<typename It11, typename It12,
		typename It21, typename It22,
		typename BinaryOperation>
	void double_iterator(It11 i_start, It12 i_end, It21 j_start, It22 j_end, BinaryOperation op);
}

#include "singleton.hpp"
#include "i_base.hpp"
#include "vector.hpp"
#include "raw_vector.hpp"
#include "files.hpp"
#include "bitmap.hpp"

#include "utils.ipp"
