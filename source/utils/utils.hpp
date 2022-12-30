/// utils.hpp

#pragma once

namespace utils
{
	inline void allocate_console()
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}
}

#include "singleton.hpp"
#include "i_base.hpp"
#include "vector.hpp"
#include "raw_vector.hpp"
#include "files.hpp"
