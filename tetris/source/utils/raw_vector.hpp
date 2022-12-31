/// raw_vector.hpp

#pragma once

template<typename T1, int N>
class raw_vector
{
private:

	vector<T1, N> data;

public:

	template<typename... Ts>
	raw_vector(Ts... args) :
		data(args...)
	{ }

	operator void* const() const
	{
		return (void*)this;
	}

	unsigned const size() const
	{
		return sizeof(T1) * N;
	}
};
