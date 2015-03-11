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
#include <eagine/meta/fold.hpp>

namespace eagine {
namespace math {

// tmat
template <typename T, unsigned R, unsigned C, bool RM>
struct tmat : matrix<T, R, C, RM>
{
private:
	typedef matrix<T, R, C, RM> _base;

public:
	constexpr inline
	tmat(void)
	noexcept
	 : _base(identity<_base>())
	{ }

	constexpr inline
	tmat(const _base& m)
	noexcept
	 : _base(m)
	{ }

	inline
	tmat(const T* d, unsigned n)
	noexcept
	 : _base(_base::from(d, n))
	{ }

private:
	template <
		typename ... P,
		typename = typename meta::enable_if<
			((sizeof...(P)) == (R*C))
		>::type
	>
	static inline
	_base _make(P&& ... p)
	{
		T d[R*C] = {T(p)...};
		return _base::from(d, R*C);
	}

	static constexpr
	bool _and(bool a, bool b)
	noexcept
	{
		return a && b;
	}

	template <typename ... P>
	struct _all_T
	 : meta::boolean_constant<
		meta::fold_with(_and, meta::is_convertible<P, T>()..., true)
	> { };
public:
	template <
		typename ... P,
		typename = typename meta::enable_if<
			((sizeof...(P)) == (R*C)) && _all_T<P...>::value
		>::type
	>
	inline
	tmat(P&& ... p)
	 : _base(_make(std::forward<P>(p)...))
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

