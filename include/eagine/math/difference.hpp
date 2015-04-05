/**
 *  @file eagine/math/difference.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_DIFFERENCE_1308281038_HPP
#define EAGINE_MATH_DIFFERENCE_1308281038_HPP

#include <limits>
#include <cmath>

namespace eagine {
namespace math {

// difference_op
template <typename T>
struct difference_op
{
	T _l, _r;

	template <typename X>
	static constexpr inline
	X _abs(X value)
	noexcept
	{
		return (value>=X(0))?value:-value;
	}

	constexpr inline
	auto get(void) const
	noexcept
	{
		return _abs(_r-_l);
	}

	constexpr inline
	operator T (void) const
	noexcept
	{
		return T(get());
	}
};

// difference
template <typename T>
static constexpr inline
difference_op<T> difference(T a, T b)
noexcept
{
	return {a, b};
}

// difference_operator fwd.
struct difference_operator { };

// half_difference_op
template <typename T>
struct half_difference_op
{
	T _l;
};

// operator << 
template <typename T>
static constexpr inline
half_difference_op<T>
operator << (T l, const difference_operator&)
noexcept
{
	return {l};
}

// operator >> 
template <typename T, typename U>
static constexpr inline
difference_op<T>
operator >> (half_difference_op<T> op, U r)
noexcept
{
	return {op._l, T(r)};
}

// operator <<to>>
static constexpr difference_operator to = {};


struct operator_equal_to;
struct operator_close_to;
struct operator_not_farther_from;

template <typename T>
struct half_operation_equal_to
{
	T _loperand;
};

template <typename T>
struct half_operation_close_to
{
	T _loperand;
};

template <typename T>
struct half_operation_not_farther_from
{
	T _loperand;
};

template <typename T>
static constexpr inline
half_operation_close_to<T>
operator << (T loperand, const operator_close_to&)
noexcept
{
	return {loperand};
}

template <typename T>
static constexpr inline
half_operation_equal_to<T>
operator << (T loperand, const operator_equal_to&)
noexcept
{
	return {loperand};
}

template <typename T>
static constexpr inline
half_operation_not_farther_from<T>
operator << (T loperand, const operator_not_farther_from&)
noexcept
{
	return {loperand};
}

template <typename T>
struct operation_close_to_operands
{
	T _loperand;
	T _roperand;

	template <typename X>
	static constexpr inline
	X _abs(X value)
	noexcept
	{
		return (value>=X(0))?value:-value;
	}

	template <typename X>
	static constexpr inline 
	X _max(X a, X b)
	noexcept
	{
		return a > b ? a : b;
	}

	template <typename X>
	static constexpr inline 
	auto _dist(X a, X b)
	noexcept
	{
		return _abs(a-b);
	}

	constexpr inline
	auto _dist(void) const
	noexcept
	{
		return _dist(_loperand,_roperand);
	}

	template <typename X>
	static constexpr inline
	auto _norm(X a, X b)
	noexcept
	{
		return _max(_abs(a),_abs(b));
	}

	constexpr inline
	auto _norm(void) const
	noexcept
	{
		return _norm(_loperand,_roperand);
	}

	template <typename X>
	static constexpr inline
	auto _adjm(T m, X n)
	noexcept
	{
		using std::pow;
		return m + T(2)*pow(X(2), -n*X(sizeof(T)*8));
	}

	template <typename X>
	static constexpr inline
	X _eps(X*)
	noexcept
	{
		return std::numeric_limits<X>::epsilon();
	}

	static constexpr inline
	T _eps(void)
	noexcept
	{
		return _eps(static_cast<T*>(nullptr));
	}

	template <typename X>
	constexpr inline
	bool _nle(X norm, T margin) const
	noexcept
	{
		return	(norm <= _eps()) ||
			(_dist()/norm <= margin);
	}

	template <typename X>
	constexpr inline
	bool _nleam(X norm, T margin) const
	noexcept
	{
		return	(norm <= _eps()) ||
			(_dist()/norm <= _adjm(margin, norm));
	}

	constexpr inline
	bool _eval_1(T margin) const
	noexcept
	{
		return _nle(T(1), margin);
	}

	constexpr inline
	bool _eval_n(T margin) const
	noexcept
	{
		return _nle(_norm(), margin);
	}

	constexpr inline
	bool _eval_nam(T margin) const
	noexcept
	{
		return _nleam(_norm(), margin);
	}
};

template <typename T>
struct full_operation_equal_to
{
	operation_close_to_operands<T> _private;

	constexpr inline
	operator bool (void) const
	noexcept
	{
		// TODO: 
		return not(_private._dist() > 0);
	}
};

template <typename T>
static constexpr inline
full_operation_equal_to<T>
operator >> (half_operation_equal_to<T> lop, T roperand)
noexcept
{
	return {{lop._loperand,roperand}};
}

template <typename T>
struct full_operation_close_to
{
	operation_close_to_operands<T> _private;

	constexpr inline
	operator bool (void) const
	noexcept
	{
		return _private._eval_1(_private._eps());
	}
};

template <typename T>
static constexpr inline
full_operation_close_to<T>
operator >> (half_operation_close_to<T> lop, T roperand)
noexcept
{
	return {{lop._loperand,roperand}};
}

template <typename T>
struct full_operation_not_farther_from
{
	struct {
		operation_close_to_operands<T> _private;

		constexpr inline
		bool abs(T margin) const
		noexcept
		{
			return _private._eval_1(margin);
		}

		constexpr inline
		bool rel(T margin) const
		noexcept
		{
			return _private._eval_n(margin);
		}

		constexpr inline
		bool eps(unsigned mult = 1u) const
		noexcept
		{
			return _private._eval_1(T(_private._eps()*mult));
		}

		constexpr inline
		bool operator()(T margin) const
		noexcept
		{
			return _private._eval_nam(margin);
		}
	} than;
};

template <typename T>
static constexpr inline
full_operation_not_farther_from<T>
operator >> (half_operation_not_farther_from<T> lop, T roperand)
noexcept
{
	return {{{lop._loperand,roperand}}};
}

struct operator_equal_to
{
	template <typename T>
	constexpr inline
	full_operation_equal_to<T>
	operator()(T loperand, T roperand) const
	noexcept
	{
		return {{loperand, roperand}};
	}
};
static constexpr operator_equal_to equal_to = {};

struct operator_close_to
{
	template <typename T>
	constexpr inline
	full_operation_close_to<T>
	operator()(T loperand, T roperand) const
	noexcept
	{
		return {{loperand, roperand}};
	}
};
static constexpr operator_close_to close_to = {};

struct operator_not_farther_from
{
	template <typename T>
	constexpr inline
	full_operation_not_farther_from<T>
	operator()(T loperand, T roperand) const
	noexcept
	{
		return {{{loperand, roperand}}};
	}
};
static constexpr operator_not_farther_from not_farther_from = {};

} // namespace math
} // namespace eagine

#endif //include guard

