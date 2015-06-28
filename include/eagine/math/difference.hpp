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
	typedef T data_type;
	T _l, _r;

	template <typename X>
	static constexpr inline
	auto _abs(X value)
	noexcept
	{
		return (value>=X(0))?value:-value;
	}

	template <typename X>
	static constexpr inline
	auto _max(X a, X b)
	noexcept
	{
		return a > b ? a : b;
	}

	template <typename X>
	static constexpr inline
	auto norm(X a, X b)
	noexcept
	{
		return _max(_abs(a),_abs(b));
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
	return difference_op<T>{a, b};
}

// difference_operator fwd.
struct difference_operator { };

// half_difference_op
template <typename T>
struct half_difference_op
{
	T _l;
};

// half_difference
template <typename T>
static constexpr inline
half_difference_op<T> half_difference(T l)
noexcept
{
	return half_difference_op<T>{l};
}


// operator <<
template <typename T>
static constexpr inline
half_difference_op<T>
operator << (T l, const difference_operator&)
noexcept
{
	return half_difference(l);
}

// operator >>
template <typename T, typename U>
static constexpr inline
difference_op<T>
operator >> (half_difference_op<T> op, U r)
noexcept
{
	return difference_op<T>{op._l, T(r)};
}

// operator <<to>>
static constexpr difference_operator to = {};

namespace cmp {

struct cmp_less_than
{
	template <typename L, typename R>
	constexpr inline
	bool operator()(L l, R r) const
	noexcept
	{
		return l < r;
	}
};

struct cmp_less_equal
{
	template <typename L, typename R>
	constexpr inline
	bool operator()(L l, R r) const
	noexcept
	{
		return l <= r;
	}
};

struct cmp_greater_than
{
	template <typename L, typename R>
	constexpr inline
	bool operator()(L l, R r) const
	noexcept
	{
		return l > r;
	}
};

template <typename Cmp>
struct operator_ : Cmp
{ };

static constexpr operator_<cmp_less_than> less_than = {};
static constexpr operator_<cmp_less_equal> less_equal = {};
static constexpr operator_<cmp_greater_than> greater_than = {};

struct zero
{
	template <typename X, typename U>
	constexpr inline
	X operator()(X, U, U) const
	noexcept
	{
		return X(0);
	}
};

struct epsilon
{
	template <typename X, typename U>
	constexpr inline
	X operator()(X, U, U) const
	noexcept
	{
		return std::numeric_limits<X>::epsilon();
	}
};

template <template <class> class Margin>
struct margin_ctr
{
	template <typename T>
	constexpr inline
	Margin<T> operator ()(T v) const
	noexcept
	{
		return Margin<T>{v};
	}
};

template <typename T>
struct val_t
{
	T _v;

	template <typename X, typename U>
	constexpr inline
	X operator()(X, U, U) const
	noexcept
	{
		return X(_v);
	}
};

static constexpr margin_ctr<val_t> exactly = {};

template <typename T>
struct rel_t
{
	T _v;

	template <typename N>
	static constexpr inline
	auto _adjn(N n)
	noexcept
	{
		using std::pow;
		return (n<N(2))?2*pow(N(2), -n*N(sizeof(T)*8)):0;
	}

	template <typename N>
	constexpr inline
	auto _get(N n) const
	noexcept
	{
		return n*(_v+_adjn(n));
	}

	template <typename X, typename V>
	constexpr inline
	auto operator ()(X, V l, V r) const
	noexcept
	{
		return X(_get(difference_op<V>::norm(l, r)));
	}
};

static constexpr margin_ctr<rel_t> relative = {};

template <typename T, typename Op>
struct difference_cmp;

template <typename T, typename Cmp>
struct difference_cmp<T, operator_<Cmp>>
{
	T _l, _r;

	template <typename D, typename M>
	static constexpr inline
	bool _cmp(D diff, T l, T r, M margin)
	noexcept
	{
		return Cmp()(diff, margin(diff, l, r));
	}

	template <typename M>
	static constexpr inline
	bool apply(T l, T r, M margin)
	noexcept
	{
		return _cmp(difference(l, r).get(), l, r, margin);
	}

	template <typename Margin>
	constexpr inline
	bool operator()(Margin margin) const
	noexcept
	{
		return apply(_l, _r, margin);
	}
};

template <typename T, typename Cmp>
static constexpr inline
difference_cmp<T, operator_<Cmp>>
operator << (difference_op<T> op, operator_<Cmp>)
noexcept
{
	return difference_cmp<T, operator_<Cmp>>{op._l, op._r};
}

template <typename T, typename Cmp, typename M>
static constexpr inline
bool
operator >> (difference_cmp<T, operator_<Cmp>> op, M margin)
noexcept
{
	return op(margin);
}

} // namespace cmp

template <typename Cmp, typename Mgn>
struct difference_operation
{
	Mgn _margin;

	template <typename T>
	constexpr inline
	bool operator ()(T loperand, T roperand) const
	noexcept
	{
		return cmp::difference_cmp<T, cmp::operator_<Cmp>>::apply(
			loperand,
			roperand,
			_margin
		);
	}
};

template <typename T, typename DiffOp>
struct half_diff_operation
{
	DiffOp _op;
	T _loperand;
};

template <typename T, typename Cmp, typename Mgn>
static constexpr inline
half_diff_operation<T, difference_operation<Cmp, Mgn>>
operator << (T loperand, const difference_operation<Cmp, Mgn>& operation)
noexcept
{
	return {operation, loperand};
}

template <typename T, typename DiffOp>
struct full_diff_operation;

template <typename T, typename Cmp, typename Mgn>
struct full_diff_operation<T, difference_operation<Cmp, Mgn>>
{
	difference_operation<Cmp, Mgn> _diff_op;
	T _loperand, _roperand;

	constexpr inline
	bool operator ()(void) const
	noexcept
	{
		return _diff_op(_loperand, _roperand);
	}

	constexpr inline
	operator bool (void) const
	noexcept
	{
		return (*this)();
	}

	constexpr inline
	bool operator ! (void) const
	noexcept
	{
		return !((*this)());
	}
};

template <typename T, typename DiffCmp>
static constexpr inline
full_diff_operation<T, DiffCmp>
operator >> (const half_diff_operation<T, DiffCmp>& lop, T roperand)
noexcept
{
	return {lop._op, lop._loperand, roperand};
}

static constexpr difference_operation<cmp::cmp_less_equal, cmp::zero>
	equal_to = {{}};

static constexpr difference_operation<cmp::cmp_less_equal, cmp::epsilon>
	close_to = {{}};

} // namespace math
} // namespace eagine

#endif //include guard

