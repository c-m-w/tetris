/// utils.inl

#pragma once

namespace utils
{
	template<typename T>
	T random_number(T const min, T const max)
	{
		return static_cast<T>(rand() % (max - min) + min);
	}

	template<> inline
	int random_number<int>(int const min, int const max)
	{
		return static_cast<int>(rand() % (max - min + 1) + min);
	}
}
