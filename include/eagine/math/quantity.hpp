/**
 *  @file eagine/math/quantity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_MATH_QUANTITY_1308281038_HPP
#define EAGINE_MATH_QUANTITY_1308281038_HPP

#include <eagine/unit/dimensionless.hpp>

namespace EAGine {
namespace math {

template <typename Unit, typename T = double>
struct quantity
{
	typedef Unit unit_type;
	typedef T value_type;

	T _v;
};

template <typename U, typename T>
static inline T value(const quantity<U, T>& q)
{
	return q._v;
}

template <typename U, typename T>
constexpr inline
bool
operator == (const quantity<U, T>& a, const quantity<U, T>& b)
{
	return a._v == b._v;
}

template <typename U, typename T>
constexpr inline
bool
operator != (const quantity<U, T>& a, const quantity<U, T>& b)
{
	return a._v != b._v;
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

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator + (const quantity<U, T>& a, const quantity<U, T>& b)
{
	return {a._v + b._v};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator - (const quantity<U, T>& a, const quantity<U, T>& b)
{
	return {a._v - b._v};
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

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator * (const quantity<U, T>& a, const quantity<unit::dimensionless, T>& b)
{
	return {a._v * b._v};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator * (const quantity<unit::dimensionless, T>& a, const quantity<U, T>& b)
{
	return {a._v * b._v};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator / (const quantity<U, T>& a, const T& c)
{
	return {a._v / c};
}

template <typename U, typename T>
constexpr inline
quantity<U, T>
operator / (const quantity<U, T>& a, const quantity<unit::dimensionless, T>& b)
{
	return {a._v / b._v};
}

template <typename U, typename T>
constexpr inline
quantity<unit::dimensionless, T>
operator / (const quantity<U, T>& a, const quantity<U, T>& b)
{
	return {a._v / b._v};
}

} // namespace math
} // namespace EAGine

#endif //include guard

