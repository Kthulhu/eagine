/**
 *  @file eagine/vect/slerp.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_SLERP_1308281038_HPP
#define EAGINE_VECT_SLERP_1308281038_HPP

#include <eagine/vect/fill.hpp>
#include <cmath>

namespace EAGine {
namespace vect {

template <typename T>
struct slerp_coefs
{
private:
	T _phi, _isin_phi;

	static constexpr T _isp(T phi)
	{
		using std::sin;
		return (sin(phi)!=0)?T(1)/sin(phi):T(0);
	}
public:
	constexpr slerp_coefs(T angle_rad)
	 : _phi(angle_rad)
	 , _isin_phi(_isp(_phi))
	{ }

	inline bool degenerate(void) const
	{
		return _isin_phi == 0;
	}

	inline bool close(T eps) const
	{
		return _phi < eps;
	}

	inline T p(T t) const
	{
		using std::sin;
		return sin((1-t)*_phi)*_isin_phi;
	}

	inline T q(T t) const
	{
		using std::sin;
		return sin(t*_phi)*_isin_phi;
	}
};

template <typename T, unsigned N>
struct slerp
{
private:
	slerp_coefs<T> _sc;
	typedef typename data<T, N>::type _dT;
public:
	constexpr slerp(T angle_rad)
	 : _sc(angle_rad)
	{ }

	inline bool degenerate(void) const
	{
		return _sc.degenerate();
	}

	inline bool close(T eps) const
	{
		return _sc.close(eps);
	}

	_dT operator ()(const _dT& a, const _dT& b, T t) const
	{
		typedef fill<T, N> _fill;
		return	a*_fill::apply(_sc.p(t))+
			b*_fill::apply(_sc.q(t));
	}
};

} // namespace vect
} // namespace EAGine

#endif //include guard

