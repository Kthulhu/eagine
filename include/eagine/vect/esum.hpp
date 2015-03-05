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

template <typename T, unsigned N>
struct esum
{
	typedef typename data_param<T, N>::type _dpT;

	static inline
	T apply(_dpT v)
	noexcept
	{
		return hsum<T,N>::apply(v)[0];
	}
};


template <typename T>
struct esum<T, 1>
{
	typedef typename data_param<T, 1>::type _dpT;

	static constexpr inline
	T apply(_dpT v)
	noexcept
	{
		return v[0];
	}
};

template <typename T>
struct esum<T, 2>
{
	typedef typename data_param<T, 2>::type _dpT;

	static constexpr inline
	T apply(_dpT v)
	noexcept
	{
		return v[0] + v[1];
	}
};

template <typename T>
struct esum<T, 3>
{
	typedef typename data_param<T, 3>::type _dpT;

	static constexpr inline
	T apply(_dpT v)
	noexcept
	{
		return v[0] + v[1] + v[2];
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

