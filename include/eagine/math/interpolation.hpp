/**
 *  @file eagine/math/interpolation.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_INTERPOLATION_1308281038_HPP
#define EAGINE_MATH_INTERPOLATION_1308281038_HPP

#include <eagine/math/quaternion.hpp>
#include <eagine/math/vector.hpp>
#include <eagine/vect/slerp.hpp>
#include <eagine/vect/lerp.hpp>
#include <utility>

namespace eagine {
namespace math {

template <typename T>
class interpolation
{
private:
	T _a, _b;
public:
	template <typename A, typename B>
	interpolation(A&& a, B&& b)
	 : _a(std::forward<A>(a))
	 , _b(std::forward<B>(b))
	{ }

	template <typename P>
	inline T operator ()(P t) const
	{
		return _a*(1-t)+_b*t;
	}
};

template <typename T, unsigned N>
class interpolation<vector<T, N>>
{
private:
	vector<T, N> _a, _b;
	vect::lerp<T, N> _vl;
public:
	interpolation(
		const vector<T, N>& a,
		const vector<T, N>& b,
		T eps=0.01
	): _a(a)
	 , _b(b)
	 , _vl()
	{ }

	inline vector<T, N> operator ()(T t) const
	{
		return {_vl(_a._v, _b._v, t)};
	}
};

template <typename T>
class interpolation<quaternion<T>>
{
private:
	quaternion<T> _a, _b;
	vect::slerp<T, 4> _vs;
	vect:: lerp<T, 4> _vl;

	quaternion<T> _fvs(T t) const
	{
		return {_vs(_a._v, _b._v, t)};
	}

	quaternion<T> _fvl(T t) const
	{
		return {_vl(_a._v, _b._v, t)};
	}

	quaternion<T> _fa(T) const
	{
		return _a;
	}

	quaternion<T> (interpolation::*_f)(T) const;
public:
	interpolation(
		const quaternion<T>& a,
		const quaternion<T>& b,
		T eps=0.01
	): _a(a)
	 , _b(b)
	 , _vs(value(angle_between(_a, _b)))
	 , _f(_vs.degenerate()?
		&interpolation::_fa:
		_vs.close(eps)?
			&interpolation::_fvl:
			&interpolation::_fvs
	)
	{ }

	inline quaternion<T> operator ()(T t) const
	{
		return (this->*_f)(t);
	}
};

} // namespace math
} // namespace eagine

#endif //include guard

