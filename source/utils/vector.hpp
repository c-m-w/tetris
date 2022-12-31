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

	template<typename T1, unsigned N1>
	vector(vector<T1, N1> rhs)
	{
		for (auto i = 0u; i < N; i++)
			this->components[i] = rhs.components[i];
	}

	// pull out first parameter so copy ctor doesnt use this
	template<class... Ts> vector(T f, Ts... args):
		components{ f, T(args)... }
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

		for (auto i = 0u; i < components.size(); i++)
			result[i] = (*this)[i] + rhs[i];

		return result;
	}

	vector<T, N>& operator+=(vector<T, N> const& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	vector<T, N> operator-(vector<T, N> const rhs) const // todo make this better. this is ass
	{
		vector<T, N> result;

		for (auto i = 0u; i < components.size(); i++)
			result[i] = (*this)[i] - rhs[i];

		return result;
	}

	vector<T, N>& operator-=(vector<T, N> const& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	vector<T, N> operator+(T const rhs) const // todo make this better. this is ass
	{
		vector<T, N> result;

		for (auto i = 0u; i < components.size(); i++)
			result[i] = (*this)[i] + rhs;

		return result;
	}

	vector<T, N> operator/(T const rhs) const // todo make this better. this is ass
	{
		vector<T, N> result;

		for (auto i = 0u; i < components.size(); i++)
			result[i] = (*this)[i] / rhs;

		return result;
	}

	vector<T, N> operator*(T const rhs) const // todo make this better. this is ass
	{
		vector<T, N> result;

		for (auto i = 0u; i < components.size(); i++)
			result[i] = (*this)[i] * rhs;

		return result;
	}

	vector<T, N> rotate2d(double const angle, bool round = false) const
	{
		vector<T, N> result = *this;

		/*
		*
		*	| x' |   | cos(angle)  -sin(angle) | | x |
		*	|    | = |                         | |   |
		*   | y' |   | sin(angle)   cos(angle) | | y |
		* 
		*/
		auto const x = std::cos(angle) * components[0] - std::sin(angle) * components[1];
		auto const y = std::sin(angle) * components[0] + std::cos(angle) * components[1];

		if (round)
		{
			result[0] = static_cast<T>(std::round(x));
			result[1] = static_cast<T>(std::round(y));
		}
		else
		{
			result[0] = static_cast<T>(x);
			result[1] = static_cast<T>(y);
		}

		return result;
	}
};
