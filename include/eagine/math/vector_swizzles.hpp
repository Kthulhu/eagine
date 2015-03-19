/**
 *  @file eagine/math/vector_swizzle.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_VECTOR_SWIZZLE_1308281038_HPP
#define EAGINE_MATH_VECTOR_SWIZZLE_1308281038_HPP

#include <eagine/math/swizzle.hpp>

namespace eagine {
namespace math {

template <typename Vector>
class vector_swizzles
 : public Vector
{
public:
	typedef typename Vector::value_type value_type;

	using Vector::Vector;

	vector_swizzles(void) = default;

	vector_swizzles(const Vector& v)
	noexcept
	 : Vector(v)
	{ }

	template <unsigned ... I>
	constexpr inline
	typename meta::enable_if<
		has_swizzle<Vector, I...>::value,
		vector_swizzles<
			typename Vector::template rebind<
				value_type,
				sizeof...(I)
			>::type
		>
	>::type swizzle(typename Vector::value_type c = 0) const
	noexcept
	{
		return eagine::math::swizzle<value_type>(
			*this,
			swizzle_mask<value_type, I...>{c}
		);
	}

#include <eagine/math/vector_swizzles.ipp>
};

} // namespace math
} // namespace eagine

#endif //include guard

