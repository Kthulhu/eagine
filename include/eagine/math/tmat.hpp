/**
 *  @file eagine/math/tmat.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_TMAT_1412182141_HPP
#define EAGINE_MATH_TMAT_1412182141_HPP

#include <eagine/math/matrix.hpp>
#include <eagine/meta/type_traits.hpp>

namespace eagine {
namespace math {

// tmat
template <typename T, unsigned R, unsigned C, bool RM>
struct tmat : matrix<T, R, C, RM>
{
	typedef matrix<T, R, C, RM> _base;

	constexpr inline
	tmat(void)
	noexcept
	 : _base(identity<_base>())
	{ }

	inline
	tmat(const T* d, unsigned n)
	noexcept
	 : _base(_base::from(d, n))
	{ }

	template <
		typename ... P,
		typename = typename meta::enable_if<
			((sizeof...(P)) == (RM?R:C))
		>::type
	>
	constexpr inline
	tmat(const vector<P, RM?C:R>&... v)
	noexcept
	 : _base{{v._v...}}
	{ }
};

// mat2
typedef tmat<float, 2, 2, true> mat2;
// mat3
typedef tmat<float, 3, 3, true> mat3;
// mat4
typedef tmat<float, 4, 4, true> mat4;

} // namespace math
} // namespace eagine

#endif //include guard

