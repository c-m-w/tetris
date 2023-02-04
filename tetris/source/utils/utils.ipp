#include "utils.hpp"
/// utils.inl

#pragma once

namespace utils
{
	template<typename T>
	T random_number(T const min, T const max)
	{
		srand(time());
		return static_cast<T>(rand() % (max - min) + min);
	}

	template<> inline
	int random_number<int>(int const min, int const max)
	{
		srand(time());
		return static_cast<int>(rand() % (max - min + 1) + min);
	}

	template<typename It11, typename It12,
		typename It21, typename It22,
		typename BinaryOperation>
	void double_iterator(It11 i_start, It12 i_end, It21 j_start, It22 j_end, BinaryOperation op)
	{
		while (i_start != i_end
			&& j_start != j_end)
			op(*i_start++, *j_start++);
	}
}
