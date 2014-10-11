/**
 *  @file eagine/vect/data.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_DATA_1308281038_HPP
#define EAGINE_VECT_DATA_1308281038_HPP

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct _ary_data
{
	T _v[N];

	inline T operator [] (unsigned i) const
	{
		return _v[i];
	}

	inline T& operator [] (unsigned i)
	{
		return _v[i];
	}

	friend inline _ary_data operator + (_ary_data a)
	{
		return a;
	}

	friend _ary_data operator - (const _ary_data& a)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = -a._v[i];
		}
		return c;
	}

	friend _ary_data operator + (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] + b._v[i];
		}
		return c;
	}

	friend _ary_data operator - (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] - b._v[i];
		}
		return c;
	}

	friend _ary_data operator * (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] * b._v[i];
		}
		return c;
	}

	friend _ary_data operator / (const _ary_data& a, const _ary_data& b)
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] / b._v[i];
		}
		return c;
	}
};

template <typename T>
struct _ary_data<T, 0u>
{
	T operator [] (unsigned i) const;
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

template <>
struct data<double, 1>
{
	typedef double type __attribute__ ((vector_size ( 8)));
};

template <>
struct data<double, 2>
{
	typedef double type __attribute__ ((vector_size (16)));
};

template <>
struct data<double, 3>
{
	typedef double type __attribute__ ((vector_size (24)));
};

template <>
struct data<double, 4>
{
	typedef double type __attribute__ ((vector_size (32)));
};

#elif defined(__GNUC__) && __SSE__

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
struct data<T,3> : _data<T,4>
{ };

template <typename T>
struct data<T,4> : _data<T,4>
{ };

#endif

} // namespace vect
} // namespace EAGine

#endif //include guard

