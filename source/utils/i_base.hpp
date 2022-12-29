/// i_base.hpp

#pragma once

template<typename _t>
class i_base : public singleton<_t>
{
public:

	virtual bool init() = 0;
	virtual bool shutdown() { return true; }
};
