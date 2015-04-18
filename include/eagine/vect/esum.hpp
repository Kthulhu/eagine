/**
 *  @file eagine/vect/esum.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_ESUM_1308281038_HPP
#define EAGINE_VECT_ESUM_1308281038_HPP

#include <eagine/vect/hsum.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct esum
{
private:
	typedef typename data_param<T, N, V>::type _dpT;

	template <unsigned M, bool B>
	static inline
	T _hlp(_dpT v, meta::unsigned_constant<M>, meta::boolean_constant<B>)
	noexcept
	{
		static_assert(M == N, "");
		T r = T(0);
		for(unsigned i=0; i<N; ++i)
		{
			r += v[i];
		}
		return r;
	}

	template <bool B>
	static constexpr inline
	T _hlp(_dpT v, meta::unsigned_constant<1>, meta::boolean_constant<B>)
	noexcept
	{
		return v[0];
	}

	template <unsigned M>
	static inline
	T _hlp(_dpT v, meta::unsigned_constant<M>, meta::true_type)
	noexcept
	{
		static_assert(M == N, "");
		return hsum<T, N, V>::apply(v)[N-1];
	}
public:
	static inline
	T apply(_dpT v)
	noexcept
	{
		return _hlp(
			v,
			meta::unsigned_constant<N>(),
			has_vect_data<T, N, V>()
		);
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

