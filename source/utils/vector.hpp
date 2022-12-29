/// vector.hpp

#pragma once

template<typename T, unsigned N>
class vector
{
private:

	std::array<T, N> components;

public:

	vector() :
		components{}
	{}

	template<class... Ts> vector(Ts... args):
		components{ T(args)... }
	{ }

	T& operator[](const unsigned i)
	{
		return components[i];
	}

	T operator[](const unsigned i) const
	{
		return components[i];
	}

	vector<T, N> operator+(vector<T, N> const rhs) const // todo make this better. this is ass
	{
		vector<T, N> result;

		for (auto i = 0; i < components.size(); i++)
			result[i] = (*this)[i] + rhs[i];

		return result;
	}
};
