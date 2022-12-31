/// coordinate.hpp

#pragma once

using relative_t = float;
using pixel_t = int;

template<typename T>
class coordinate: public vector<T, 3>
{};

template<>
class coordinate<relative_t> : public vector<relative_t, 3>
{
public:
	
	template<typename... Ts>
	coordinate(Ts... args):
		vector<relative_t, 3>(args...)
	{ }
};

template<>
class coordinate<pixel_t> : public vector<pixel_t, 3>
{
public:

	template<typename... Ts>
	coordinate(Ts... args) :
		vector<pixel_t, 3>(args...)
	{ }

	coordinate<relative_t> to_relative() const
	{
		return coordinate<relative_t>(
			relative_t((*this)[0] * 2.f / WINDOW_WIDTH - 1.f),
			relative_t((*this)[1] * -2.f / WINDOW_HEIGHT + 1.f)
		);
	};
};
