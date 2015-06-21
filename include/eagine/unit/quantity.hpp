/**
 *  @file eagine/quantity/quantity.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_QUANTITY_1308281038_HPP
#define EAGINE_UNIT_QUANTITY_1308281038_HPP

#include <eagine/unit/fwd.hpp>
#include <eagine/unit/traits.hpp>
#include <eagine/unit/dimensionless.hpp>
#include <eagine/math/difference.hpp>
#include <eagine/meta/type_traits.hpp>

namespace eagine {
namespace unit {

template <typename Unit, typename T>
struct quantity
{
	typedef Unit unit_type;
	typedef T value_type;

	T _v;

	constexpr quantity(void) = default;
	constexpr quantity(const quantity&) = default;
	quantity& operator = (const quantity&) = default;

	explicit constexpr
	quantity(T v)
	noexcept
	 : _v(v)
	{ }

	template <typename UX, typename X>
	constexpr quantity(
		const quantity<UX, X>& q,
		typename meta::enable_if<
			same_dimension<Unit, UX>::value
		>::type* = 0
	): _v(value_conv<UX, Unit>::type::apply(q._v))
	{ }

	quantity& operator += (const quantity& q)
	noexcept
	{
		_v += q._v;
		return *this;
	}

	quantity& operator -= (const quantity& q)
	noexcept
	{
		_v -= q._v;
		return *this;
	}
};

template <typename S, typename T>
struct quantity<unit<dimensionless, S>, T>
{
	typedef unit<dimensionless, S> unit_type;
	typedef T value_type;

	T _v;

	constexpr quantity(void) = default;
	constexpr quantity(const quantity&) = default;
	quantity& operator = (const quantity&) = default;

	explicit constexpr
	quantity(T v)
	noexcept
	 : _v(v)
	{ }

	constexpr inline
	operator T (void) const
	noexcept
	{
		return _v;
	}
};

template <typename US, typename S, typename T>
struct quantity<scaled_unit<dimensionless, US, S>, T>
{
	typedef scaled_unit<dimensionless, US, S> unit_type;
	typedef T value_type;

	T _v;

	constexpr quantity(void) = default;
	constexpr quantity(const quantity&) = default;
	quantity& operator = (const quantity&) = default;

	explicit constexpr
	quantity(T v)
	noexcept
	 : _v(v)
	{ }

	constexpr inline
	operator T (void) const
	noexcept
	{
		return _v;
	}
};


template <typename U, typename T>
static inline T value(const quantity<U, T>& q)
{
	return q._v;
}

template <typename U1, typename U2, typename T>
constexpr inline
bool operator == (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename value_conv<U2, U1>::type conv;
	return (a._v == conv::apply(b._v));
}

template <typename U1, typename U2, typename T>
constexpr inline
bool operator != (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename value_conv<U2, U1>::type conv;
	return a._v != conv::apply(b._v);
}

template <typename U1, typename U2, typename T>
constexpr inline
bool operator <  (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename value_conv<U2, U1>::type conv;
	return a._v <  conv::apply(b._v);
}

template <typename U1, typename U2, typename T>
constexpr inline
bool operator <= (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename value_conv<U2, U1>::type conv;
	return a._v <= conv::apply(b._v);
}

template <typename U1, typename U2, typename T>
constexpr inline
bool operator >  (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename value_conv<U2, U1>::type conv;
	return a._v >  conv::apply(b._v);
}

template <typename U1, typename U2, typename T>
constexpr inline
bool operator >= (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename value_conv<U2, U1>::type conv;
	return a._v >= conv::apply(b._v);
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator + (const quantity<U, T>& a)
{
	return quantity<U, T>{a._v};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator - (const quantity<U, T>& a)
{
	return quantity<U, T>{-a._v};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename add_result<U1, U2>::type, T>
operator + (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename add_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return quantity<typename add_result<U1, U2>::type, T>
		{conv1::apply(a._v) + conv2::apply(b._v)};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename sub_result<U1, U2>::type, T>
operator - (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename sub_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return quantity<typename sub_result<U1, U2>::type, T>
		{conv1::apply(a._v) - conv2::apply(b._v)};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename mul_result<U1, U2>::type, T>
operator * (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename mul_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return quantity<typename mul_result<U1, U2>::type, T>
		{conv1::apply(a._v) * conv2::apply(b._v)};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator * (const quantity<U, T>& a, const T& c)
{
	return quantity<U, T>{a._v * c};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator * (const T& c, const quantity<U, T>& a)
{
	return quantity<U, T>{c * a._v};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename div_result<U1, U2>::type, T>
operator / (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename div_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return quantity<typename div_result<U1, U2>::type, T>
		{conv1::apply(a._v) / conv2::apply(b._v)};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator / (const quantity<U, T>& a, const T& c)
{
	return quantity<U, T>{a._v / c};
}

} // namespace quantity

namespace math {

// difference_op
template <typename U, typename T>
struct difference_op<unit::quantity<U, T>>
{
	unit::quantity<U,T> _l, _r;

	constexpr inline
	T get(void) const
	noexcept
	{
		using unit::value;
		return difference(value(_l), value(_r));
	}

	constexpr inline
	operator T (void) const
	noexcept
	{
		return get();
	}
};

} // namespace math
} // namespace eagine

#endif //include guard

