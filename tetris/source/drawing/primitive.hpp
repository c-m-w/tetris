/// primitive.hpp

// deprecated

#pragma once

class primitive
{
private:

	vector<coordinate<relative_t>, 3> v;

public:

	template<typename... Ts>
	primitive(Ts... vargs) :
		v(vargs...)
	{ }

	float* const data() const
	{
		return static_cast<float*>((void*)this);
	}
};
