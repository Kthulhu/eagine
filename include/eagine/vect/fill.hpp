/**
 *  @file eagine/vect/fill.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_FILL_1308281038_HPP
#define EAGINE_VECT_FILL_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct fill
{
	static
	typename data<T, N>::type
	apply(T v)
	noexcept
	{
		typename data<T, N>::type r;
		for(unsigned i=0; i<N; ++i)
		{
			r[i] = v;
		}
		return r;
	}
};

template <typename T>
struct fill<T, 0>
{
	static constexpr
	typename data<T, 0>::type
	apply(T)
	noexcept
	{
		return {};
	}
};

template <typename T>
struct fill<T, 1>
{
	static constexpr
	typename data<T, 1>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 1>::type
			{v};
	}
};

template <typename T>
struct fill<T, 2>
{
	static constexpr
	typename data<T, 2>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 2>::type
			{v,v};
	}
};

template <typename T>
struct fill<T, 3>
{
	static constexpr
	typename data<T, 3>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 3>::type
			{v,v,v};
	}
};

template <typename T>
struct fill<T, 4>
{
	static constexpr
	typename data<T, 4>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 4>::type
			{v,v,v,v};
	}
};

template <typename T>
struct fill<T, 8>
{
	static constexpr
	typename data<T, 8>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 8>::type
			{v,v,v,v,v,v,v,v};
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

