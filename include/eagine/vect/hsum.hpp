/**
 *  @file eagine/vect/hsum.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_HSUM_1308281038_HPP
#define EAGINE_VECT_HSUM_1308281038_HPP

#include <eagine/vect/shuffle.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct hsum
{
private:
	typedef typename data<T, N, V>::type _dT;
	typedef typename data_param<T, 1, V>::type _dpT;
	typedef shuffle<T, N, V> _sh;

	template <unsigned M, bool B>
	static
	_dT _hlp(
		_dT v,
		meta::unsigned_constant<M>,
		meta::boolean_constant<B>
	) noexcept
	{
		static_assert(M == N, "");

		for(unsigned i=1; i<N; ++i)
		{
			v[i] += v[i-1];
		}
		for(unsigned i=N-1; i>0; --i)
		{
			v[i-1] = v[i];
		}
		return v;
	}

#if EAGINE_VECT_OPTS
	template <bool B>
	static constexpr inline
	_dT _hlp(
		_dT v,
		meta::unsigned_constant<1>,
		meta::boolean_constant<B>
	) noexcept
	{
		return v;
	}

	static constexpr inline
	_dT _hlp(
		_dpT v,
		meta::unsigned_constant<2>,
		meta::boolean_constant<true>
	) noexcept
	{
		return v + _sh::template apply<1,0>(v);
	}

	static constexpr inline
	_dT _hlp3_1(_dpT t, _dpT v)
	noexcept
	{
		return t + _sh::template apply<2,2,1>(v);
	}


	static constexpr inline
	_dT _hlp(
		_dpT v,
		meta::unsigned_constant<3>,
		meta::boolean_constant<true>
	) noexcept
	{
		return _hlp3_1(v + _sh::template apply<1,0,0>(v), v);
	}

	static constexpr inline
	_dT _hlp4_1(_dpT v)
	noexcept
	{
		return v + _sh::template apply<2,3,0,1>(v);
	}

	static constexpr inline
	_dT _hlp(
		_dpT v,
		meta::unsigned_constant<4>,
		meta::boolean_constant<true>
	) noexcept
	{
		return _hlp4_1(v + _sh::template apply<1,0,3,2>(v));
	}

	static constexpr inline
	_dT _hlp8_1(_dpT v)
	noexcept
	{
		return v + _sh::template apply<1,0,3,2,5,4,7,6>(v);
	}

	static constexpr inline
	_dT _hlp8_2(_dpT v)
	noexcept
	{
		return v + _sh::template apply<2,3,0,1,6,7,4,5>(v);
	}

	static constexpr inline
	_dT _hlp8_3(_dpT v)
	noexcept
	{
		return v + _sh::template apply<4,5,6,7,0,1,2,3>(v);
	}

	static constexpr inline
	_dT _hlp(
		_dpT v,
		meta::unsigned_constant<8>,
		meta::boolean_constant<true>
	) noexcept
	{
		return _hlp8_3(_hlp8_2(_hlp8_1(v)));
	}
#endif
public:
	static inline
	_dT apply(_dT v)
	noexcept
	{
		return _hlp(
			v,
			meta::unsigned_constant<N>(),
			has_vect_data<T,N,V>()
		);
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

