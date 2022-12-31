/// utils.hpp

#pragma once

namespace utils
{
	inline void allocate_console()
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}

	inline unsigned long long time()
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
}

#include "singleton.hpp"
#include "i_base.hpp"
#include "vector.hpp"
#include "raw_vector.hpp"
#include "files.hpp"
#include "bitmap.hpp"

#include "utils.ipp"
