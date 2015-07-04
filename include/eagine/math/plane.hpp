/**
 *  @file eagine/math/plane.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_PLANE_1412222117_HPP
#define EAGINE_MATH_PLANE_1412222117_HPP

#include <eagine/math/tvec.hpp>

namespace eagine {
namespace math {

template <typename T, bool V = true>
class plane
{
private:
	vector<T, 4, V> _equation;
public:
	constexpr
	plane(T a, T b, T c, T d)
	noexcept
	 : _equation{{a, b, c, d}}
	{ }

	constexpr
	explicit plane(const vector<T, 4, V>& v)
	noexcept
	 : _equation(v)
	{ }

	static constexpr inline
	plane from_point_and_normal(
		const vector<T, 3, V>& v,
		const vector<T, 3, V>& p
	) noexcept
	{
		return plane(tvec<T, 4, V>(v,-dot(v, p)));
	}

	static constexpr inline
	plane from_triangle(
		const vector<T, 3, V>& a,
		const vector<T, 3, V>& b,
		const vector<T, 3, V>& c
	) noexcept
	{
		return from_point_and_normal(normalized(cross(b-a, c-a)), a);
	}

	static constexpr inline
	plane from_point_and_vectors(
		const vector<T, 3, V>& p,
		const vector<T, 3, V>& u,
		const vector<T, 3, V>& v
	) noexcept
	{
		return from_point_and_normal(normalized(cross(u, v)), p);
	}

	constexpr inline
	const vector<T, 4, V>& equation(void) const
	noexcept
	{
		return _equation;
	}
};

} // namespace math
} // namespace eagine

#endif //include guard

