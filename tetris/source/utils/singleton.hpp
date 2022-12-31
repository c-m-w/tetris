/// singleton.hpp

#pragma once

template<typename _t>
class singleton
{
public:

	static _t* get()
	{
		static _t inst {};

		return &inst;
	}
};
