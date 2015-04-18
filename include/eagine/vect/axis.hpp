/**
 *  @file eagine/vect/axis.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_AXIS_1308281038_HPP
#define EAGINE_VECT_AXIS_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, unsigned I, bool V>
struct axis
{
	static
	typename data<T, N, V>::type
	apply(T v)
	noexcept
	{
		typename data<T, N, V>::type r;
		for(unsigned i=0; i<N; ++i)
		{
			r[i] = (i == I)?v:T(0);
		}
		return r;
	}
};

template <typename T, bool V>
struct axis<T, 1, 0, V>
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

template <typename T, unsigned I, bool V>
struct axis<T, 1, I, V>
{
	static constexpr
	typename data<T, 1, V>::type
	apply(T)
	noexcept
	{
		return typename data<T, 1, V>::type
			{0};
	}
};

template <typename T, bool V>
struct axis<T, 2, 0, V>
{
	static constexpr
	typename data<T, 2, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 2, V>::type
			{v,T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 2, 1, V>
{
	static constexpr
	typename data<T, 2, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 2, V>::type
			{T(0),v};
	}
};

template <typename T, unsigned I, bool V>
struct axis<T, 2, I, V>
{
	static constexpr
	typename data<T, 2, V>::type
	apply(T)
	noexcept
	{
		return typename data<T, 2, V>::type
			{T(0),T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 3, 0, V>
{
	static constexpr
	typename data<T, 3, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 3, V>::type
			{v,T(0),T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 3, 1, V>
{
	static constexpr
	typename data<T, 3, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 3, V>::type
			{T(0),v,T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 3, 2, V>
{
	static constexpr
	typename data<T, 3, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 3, V>::type
			{T(0),T(0),v};
	}
};

template <typename T, unsigned I, bool V>
struct axis<T, 3, I, V>
{
	static constexpr
	typename data<T, 3, V>::type
	apply(T)
	noexcept
	{
		return typename data<T, 3, V>::type
			{T(0),T(0),T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 4, 0, V>
{
	static constexpr
	typename data<T, 4, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 4, V>::type
			{v,T(0),T(0),T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 4, 1, V>
{
	static constexpr
	typename data<T, 4, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 4, V>::type
			{T(0),v,T(0),T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 4, 2, V>
{
	static constexpr
	typename data<T, 4, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 4, V>::type
			{T(0),T(0),v,T(0)};
	}
};

template <typename T, bool V>
struct axis<T, 4, 3, V>
{
	static constexpr
	typename data<T, 4, V>::type
	apply(T v)
	noexcept
	{
		return typename data<T, 4, V>::type
			{T(0),T(0),T(0),v};
	}
};

template <typename T, unsigned I, bool V>
struct axis<T, 4, I, V>
{
	static constexpr
	typename data<T, 4, V>::type
	apply(T)
	noexcept
	{
		return typename data<T, 4, V>::type
			{T(0),T(0),T(0),T(0)};
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

