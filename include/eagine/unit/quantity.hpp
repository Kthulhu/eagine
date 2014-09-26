/**
 *  @file eagine/quantity/quantity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_QUANTITY_1308281038_HPP
#define EAGINE_UNIT_QUANTITY_1308281038_HPP

#include <eagine/unit/unit.hpp>

namespace EAGine {
namespace unit {

template <typename Unit, typename T = double>
struct quantity
{
	typedef Unit unit_type;
	typedef T value_type;

	T _v;

	template <typename UX, typename X>
	operator quantity<UX, X> (void) const
	{
		typedef typename value_conv<Unit, UX>::type conv;
		return {X(conv::apply(_v))};
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
	return a._v == conv::apply(b._v);
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
	return {a._v};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator - (const quantity<U, T>& a)
{
	return {-a._v};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename add_result<U1, U2>::type, T>
operator + (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename add_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return {conv1::apply(a._v) + conv2::apply(b._v)};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename sub_result<U1, U2>::type, T>
operator - (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename sub_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return {conv1::apply(a._v) - conv2::apply(b._v)};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename mul_result<U1, U2>::type, T>
operator * (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename mul_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return {conv1::apply(a._v) * conv2::apply(b._v)};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator * (const quantity<U, T>& a, const T& c)
{
	return {a._v * c};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator * (const T& c, const quantity<U, T>& a)
{
	return {c * a._v};
}

template <typename U1, typename U2, typename T>
constexpr inline
quantity<typename div_result<U1, U2>::type, T>
operator / (const quantity<U1, T>& a, const quantity<U2, T>& b)
{
	typedef typename div_result<U1, U2>::type UR;
	typedef typename value_conv<U1, UR>::type conv1;
	typedef typename value_conv<U2, UR>::type conv2;
	return {conv1::apply(a._v) / conv2::apply(b._v)};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator / (const quantity<U, T>& a, const T& c)
{
	return {a._v / c};
}

} // namespace quantity
} // namespace EAGine

#endif //include guard

