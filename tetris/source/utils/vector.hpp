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
		components = rhs.components;
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

	bool operator==(vector<T, N> const rhs) const
	{
		auto result = true;
		auto const p = &result;

		utils::double_iterator(components.cbegin(), components.cend(),
			rhs.components.cbegin(), rhs.components.cend(),
			[p](T const lhs, T const rhs) mutable { 
				*p &= lhs == rhs; 
			});

		return result;
	}

	vector<T, N> operator+(vector<T, N> const rhs) const
	{
		auto result = rhs;

		std::transform(components.cbegin(), 
					   components.cend(),
					   result.components.cbegin(),
					   result.components.begin(),
					   std::plus<>{});

		return result;
	}

	vector<T, N>& operator+=(vector<T, N> const& rhs)
	{
		return *this = *this + rhs;
	}

	vector<T, N> operator-(vector<T, N> const rhs) const
	{
		auto result = rhs;

		std::transform(components.cbegin(),
					   components.cend(),
					   result.components.cbegin(),
					   result.components.begin(),
					   std::minus<>{});

		return result;
	}

	vector<T, N>& operator-=(vector<T, N> const& rhs)
	{
		return *this = *this - rhs;
	}

	vector<T, N> operator+(T const rhs) const
	{
		auto result = *this;

		std::transform(result.components.cbegin(),
					   result.components.cend(),
					   result.components.begin(),
					   [rhs](T const c) { return c + rhs; });

		return result;
	}

	vector<T, N> operator/(T const rhs) const
	{
		auto result = *this;

		std::transform(result.components.cbegin(),
					   result.components.cend(),
					   result.components.begin(),
					   [rhs](T const c) { return c / rhs; });

		return result;
	}

	vector<T, N> operator*(T const rhs) const
	{
		auto result = *this;

		std::transform(result.components.cbegin(),
					   result.components.cend(),
					   result.components.begin(),
					   [rhs](T const c) { return c * rhs; });

		return result;
	}

	vector<T, N> rotate2d(double const angle, bool round = false) const
	{
		auto result = *this;

		/*
		*
		*	| x' |   | cos(angle)  -sin(angle) | | x |
		*	|    | = |                         | |   |
		*	| y' |   | sin(angle)   cos(angle) | | y |
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
