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

#include <eagine/meta/type_traits.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct _ary_data
{
	T _v[N];

	_ary_data(void) = default;
	_ary_data(const _ary_data&) = default;

	template <
		typename ... P,
		typename = typename std::enable_if<sizeof...(P) == N>::type
	>
	constexpr
	_ary_data(P&& ... p)
	 : _v{T(p)...}
	{ }

	constexpr inline
	T operator [] (unsigned i) const
	noexcept
	{
		return _v[i];
	}

	inline
	T& operator [] (unsigned i)
	noexcept
	{
		return _v[i];
	}

	friend constexpr inline
	_ary_data operator + (_ary_data a)
	noexcept
	{
		return a;
	}

	friend
	_ary_data operator - (const _ary_data& a)
	noexcept
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = -a._v[i];
		}
		return c;
	}

	friend
	_ary_data operator + (const _ary_data& a, const _ary_data& b)
	noexcept
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] + b._v[i];
		}
		return c;
	}

	friend
	_ary_data operator - (const _ary_data& a, const _ary_data& b)
	noexcept
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] - b._v[i];
		}
		return c;
	}

	friend
	_ary_data operator * (const _ary_data& a, const _ary_data& b)
	noexcept
	{
		_ary_data c;
		for(unsigned i=0; i<N; ++i)
		{
			c._v[i] = a._v[i] * b._v[i];
		}
		return c;
	}

	friend
	_ary_data operator / (const _ary_data& a, const _ary_data& b)
	noexcept
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

template <typename T, unsigned N>
struct data_param
{
	typedef const _ary_data<T, N>& type;
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

#if (defined(__clang__) || defined(__GNUC__)) && __SSE__

template <typename T>
struct data_param<T,1> : data<T,1>
{ };

template <typename T>
struct data_param<T,2> : data<T,2>
{ };

template <typename T>
struct data_param<T,3> : data<T,3>
{ };

template <typename T>
struct data_param<T,4> : data<T,4>
{ };

#endif

template <typename Data>
struct param;

template <typename T, unsigned N>
struct param<data<T, N>>
 : data_param<T, N>
{ };

} // namespace vect
} // namespace eagine

#endif //include guard

