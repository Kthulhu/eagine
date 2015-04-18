/**
 *  @file eagine/vect/from.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_FROM_1308281038_HPP
#define EAGINE_VECT_FROM_1308281038_HPP

#include <eagine/vect/data.hpp>
#include <cassert>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct from_array
{
	static
	typename data<T, N, V>::type
	apply(const T* d, std::size_t n)
	noexcept
	{
		assert(N <= unsigned(n));
		typename data<T, N, V>::type r;
		for(unsigned i=0; i<N; ++i)
		{
			r[i] = d[i];
		}
		return r;
	}
};

// from shorter array and fallback value
template <typename T, unsigned N, bool V>
struct from_saafv
{
	static
	typename data<T, N, V>::type
	apply(const T* d, std::size_t n, T v)
	noexcept
	{
		typename data<T, N, V>::type r = {};
		for(unsigned i=0; i<N && i<unsigned(n); ++i)
		{
			r[i] = d[i];
		}
		for(unsigned i=unsigned(n); i<N; ++i)
		{
			r[i] = v;
		}
		return r;
	}
};

template <typename T, bool V>
struct from_array<T, 0, V>
{
	static constexpr
	typename data<T, 0, V>::type
	apply(const T*, unsigned)
	noexcept
	{
		return {};
	}
};

template <typename T, bool V>
struct from_array<T, 1, V>
{
	static
	typename data<T, 1, V>::type
	apply(const T* d, std::size_t n)
	noexcept
	{
		assert(1 <= n);
		return typename data<T, 1, V>::type
			{d[0]};
	}
};

template <typename T, bool V>
struct from_array<T, 2, V>
{
	static
	typename data<T, 2, V>::type
	apply(const T* d, std::size_t n)
	noexcept
	{
		assert(2 <= n);
		return typename data<T, 2, V>::type
			{d[0], d[1]};
	}
};

template <typename T, bool V>
struct from_array<T, 3, V>
{
	static
	typename data<T, 3, V>::type
	apply(const T* d, std::size_t n)
	noexcept
	{
		assert(3 <= n);
		return typename data<T, 3, V>::type
			{d[0], d[1], d[2]};
	}
};

template <typename T, bool V>
struct from_array<T, 4, V>
{
	static
	typename data<T, 4, V>::type
	apply(const T* d, std::size_t n)
	noexcept
	{
		assert(4 <= n);
		return typename data<T, 4, V>::type
			{d[0], d[1], d[2], d[3]};
	}
};

template <typename T, bool V>
struct from_array<T, 8, V>
{
	static
	typename data<T, 8, V>::type
	apply(const T* d, std::size_t n)
	noexcept
	{
		assert(8 <= n);
		return typename data<T, 8, V>::type
			{d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7]};
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

