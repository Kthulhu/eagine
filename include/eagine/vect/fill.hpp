/**
 *  @file eagine/vect/fill.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_FILL_1308281038_HPP
#define EAGINE_VECT_FILL_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct fill
{
	static
	typename data<T, N, V>::type
	apply(T v)
	noexcept
	{
		typename data<T, N, V>::type r;
		for(unsigned i=0; i<N; ++i)
		{
			r[i] = v;
		}
		return r;
	}
};

#if EAGINE_VECT_OPTS

template <typename T, bool V>
struct fill<T, 0, V>
{
	static constexpr
	typename data<T, 0, V>::type
	apply(T)
	noexcept
	{
		return {};
	}
};

template <typename T, bool V>
struct fill<T, 1, V>
{
	static constexpr
	typename data<T, 1, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 1, V>::type
			{v};
	}
};

template <typename T, bool V>
struct fill<T, 2, V>
{
	static constexpr
	typename data<T, 2, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 2, V>::type
			{v,v};
	}
};

template <typename T, bool V>
struct fill<T, 3, V>
{
	static constexpr
	typename data<T, 3, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 3, V>::type
			{v,v,v};
	}
};

template <typename T, bool V>
struct fill<T, 4, V>
{
	static constexpr
	typename data<T, 4, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 4, V>::type
			{v,v,v,v};
	}
};

template <typename T, bool V>
struct fill<T, 8, V>
{
	static constexpr
	typename data<T, 8, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 8, V>::type
			{v,v,v,v,v,v,v,v};
	}
};

#endif

} // namespace vect
} // namespace eagine

#endif //include guard

