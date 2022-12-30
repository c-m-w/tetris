/// files.hpp

#pragma once

namespace utils
{
	inline std::string current_path()
	{
		return std::filesystem::current_path().u8string();
	}
}
