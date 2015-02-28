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

template <typename T, unsigned N>
struct from_array
{
	static
	typename data<T, N>::type
	apply(const T* d, unsigned n)
	noexcept
	{
		assert(N <= n);
		typename data<T, N>::type r;
		for(unsigned i=0; i<N; ++i)
		{
			r[i] = d[i];
		}
		return r;
	}
};

// from shorter array and fallback value
template <typename T, unsigned N>
struct from_saafv
{
	static
	typename data<T, N>::type
	apply(const T* d, unsigned n, T v)
	noexcept
	{
		typename data<T, N>::type r;
		for(unsigned i=0; i<N && i<n; ++i)
		{
			r[i] = d[i];
		}
		for(unsigned i=n; i<N; ++i)
		{
			r[i] = v;
		}
		return r;
	}
};

template <typename T>
struct from_array<T, 0>
{
	static constexpr
	typename data<T, 0>::type
	apply(const T*, unsigned)
	noexcept
	{
		return {};
	}
};

template <typename T>
struct from_array<T, 1>
{
	static
	typename data<T, 1>::type
	apply(const T* d, unsigned n)
	noexcept
	{
		assert(1 <= n);
		return typename data<T, 1>::type
			{d[0]};
	}
};

template <typename T>
struct from_array<T, 2>
{
	static
	typename data<T, 2>::type
	apply(const T* d, unsigned n)
	noexcept
	{
		assert(2 <= n);
		return typename data<T, 2>::type
			{d[0], d[1]};
	}
};

template <typename T>
struct from_array<T, 3>
{
	static
	typename data<T, 3>::type
	apply(const T* d, unsigned n)
	noexcept
	{
		assert(3 <= n);
		return typename data<T, 3>::type
			{d[0], d[1], d[2]};
	}
};

template <typename T>
struct from_array<T, 4>
{
	static
	typename data<T, 4>::type
	apply(const T* d, unsigned n)
	noexcept
	{
		assert(4 <= n);
		return typename data<T, 4>::type
			{d[0], d[1], d[2], d[3]};
	}
};

template <typename T>
struct from_array<T, 8>
{
	static
	typename data<T, 8>::type
	apply(const T* d, unsigned n)
	noexcept
	{
		assert(8 <= n);
		return typename data<T, 8>::type
			{d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7]};
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

