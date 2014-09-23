/**
 *  @file eagine/vect/data.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_VECT_DATA_1308281038_HPP
#define EAGINE_VECT_DATA_1308281038_HPP

#include <array>

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct _ary_data : std::array<T, N>
{
	friend inline _ary_data operator + (_ary_data a)
	{
		return a;
	}

	friend _ary_data operator - (const _ary_data& a)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = -a[i];
		}
		return c;
	}

	friend _ary_data operator - (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = a[i] - b[i];
		}
		return c;
	}

	friend _ary_data operator * (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = a[i] * b[i];
		}
		return c;
	}

	friend _ary_data operator / (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = a[i] / b[i];
		}
		return c;
	}
};

template <typename T, unsigned N>
struct data
{
	typedef _ary_data<T, N> type;
};

#if defined(__clang__) && __SSE__

template <>
struct data<float, 1>
{
	typedef float type __attribute__ ((vector_size ( 4)));
};

template <>
struct data<float, 2>
{
	typedef float type __attribute__ ((vector_size ( 8)));
};

template <>
struct data<float, 3>
{
	typedef float type __attribute__ ((vector_size (12)));
};

template <>
struct data<float, 4>
{
	typedef float type __attribute__ ((vector_size (16)));
};

#elif defined(__GNUC__)

template <typename T, unsigned N>
struct _data
{
	typedef T type __attribute__ ((vector_size (sizeof(T)*N)));
};

template <typename T>
struct data<T,1> : _data<T,1>
{ };

template <typename T>
struct data<T,2> : _data<T,2>
{ };

template <typename T>
struct data<T,3> : _data<T,3>
{ };

template <typename T>
struct data<T,4> : _data<T,4>
{ };

#else

#endif

} // namespace vect
} // namespace EAGine

#endif //include guard

