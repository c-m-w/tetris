/// primitive_color.hpp

// deprecated

#pragma once

using color_t = vector<float, 3>;

class primitive_color
{
private:

	vector<color_t, 3> color;

public:

	template<typename... Ts>
	primitive_color(Ts... args) :
		color(args...)
	{ }

	operator float* () const
	{
		return static_cast<float*>((void*)this);
	}
};
