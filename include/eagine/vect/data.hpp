/**
 *  @file eagine/vect/data.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_DATA_1308281038_HPP
#define EAGINE_VECT_DATA_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/vect/config.hpp>
#include <utility>
#include <cstdint>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct _ary_data
{
	T _v[N];

	typedef _ary_data type;

	_ary_data(void) = default;
	_ary_data(const _ary_data& that) = default;
	_ary_data& operator=(const _ary_data& that) = default;

	template <
		typename ... P,
		typename = typename meta::enable_if<
			(N > 1) && (sizeof...(P) == N)
		>::type
	>
	constexpr
	_ary_data(P&& ... p)
	 : _v{T(std::forward<P>(p))...}
	{ }

	template <
		typename P,
		typename = typename meta::enable_if<
			(N == 1) && (meta::is_convertible<P, T>::value)
		>::type
	>
	constexpr
	_ary_data(P&& p)
	 : _v{T(std::forward<P>(p))}
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
	_ary_data operator - (_ary_data a)
	noexcept
	{
		for(unsigned i=0; i<N; ++i)
		{
			a._v[i] = -a._v[i];
		}
		return a;
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

template <typename T, unsigned N>
struct _ary_cref
{
	typedef const _ary_data<T, N>& type;
};

template <typename T>
struct _ary_data<T, 0u>
{
	typedef _ary_data type;

	T operator [] (unsigned i) const;
};

template <typename T, unsigned N>
struct _vec_data;

template <typename T, unsigned N>
struct _has_vec_data
 : meta::false_type
{ };

#if EAGINE_USE_SIMD
#if defined(__clang__)

// int8_t
template <>
struct _vec_data<int8_t, 8>
{
	typedef int8_t type __attribute__ ((vector_size ( 8)));
};

// int16_t
template <>
struct _vec_data<int16_t, 4>
{
	typedef int16_t type __attribute__ ((vector_size ( 8)));
};

// int32_t
template <>
struct _vec_data<int32_t, 2>
{
	typedef int32_t type __attribute__ ((vector_size ( 8)));
};

template <>
struct _vec_data<int32_t, 4>
{
	typedef int32_t type __attribute__ ((vector_size (16)));
};

// int64_t
template <>
struct _vec_data<int64_t, 2>
{
	typedef int64_t type __attribute__ ((vector_size (16)));
};

template <>
struct _vec_data<int64_t, 4>
{
	typedef int64_t type __attribute__ ((vector_size (32)));
};

// float
template <>
struct _vec_data<float, 2>
{
	typedef float type __attribute__ ((vector_size ( 8)));
};

template <>
struct _vec_data<float, 3>
{
	typedef float type __attribute__ ((vector_size (16)));
};

template <>
struct _vec_data<float, 4>
{
	typedef float type __attribute__ ((vector_size (16)));
};

// double
template <>
struct _vec_data<double, 2>
{
	typedef double type __attribute__ ((vector_size (16)));
};

template <>
struct _vec_data<double, 3>
{
	typedef double type __attribute__ ((vector_size (32)));
};

template <>
struct _vec_data<double, 4>
{
	typedef double type __attribute__ ((vector_size (32)));
};

#elif defined(__GNUC__)

template <typename T, unsigned N>
struct _gnuc_vec_data
{
	typedef T type __attribute__ ((vector_size (sizeof(T)*N)));
};

template <typename T>
struct _vec_data<T,2> : _gnuc_vec_data<T,2>
{ };

template <typename T>
struct _vec_data<T,3> : _gnuc_vec_data<T,4>
{ };

template <typename T>
struct _vec_data<T,4> : _gnuc_vec_data<T,4>
{ };

template <typename T>
struct _vec_data<T,8> : _gnuc_vec_data<T,8>
{ };

#endif // platform

// has_vec_data<int8_t>
template <unsigned N>
struct _has_vec_data<int8_t, N>
 : meta::boolean_constant<
#if defined(__SSE2__) && __SSE2__
	((N==2)||(N==4)||(N==8)||(N==16)) ||
#endif
#if defined(__MMX__) && __MMX__
	((N==2)||(N==4)||(N==8)) ||
#endif
	false
>
{ };

// has_vec_data<int16_t>
template <unsigned N>
struct _has_vec_data<int16_t, N>
 : meta::boolean_constant<
#if defined(__SSE2__) && __SSE2__
	((N==2)||(N==4)||(N==8)) ||
#endif
#if defined(__MMX__) && __MMX__
	((N==2)||(N==4)) ||
#endif
	false
>
{ };

// has_vec_data<int32_t>
template <unsigned N>
struct _has_vec_data<int32_t, N>
 : meta::boolean_constant<
#if defined(__SSE2__) && __SSE2__
	((N==2)||(N==4)) ||
#endif
#if defined(__MMX__) && __MMX__
	(N==2) ||
#endif
	false
>
{ };

// has_vec_data<int64_t>
template <unsigned N>
struct _has_vec_data<int64_t, N>
 : meta::boolean_constant<
#if defined(__SSE2__) && __SSE2__
	(N==2) ||
#endif
	false
>
{ };

// has_vec_data<float>
template <unsigned N>
struct _has_vec_data<float, N>
 : meta::boolean_constant<
#if defined(__AVX__) && __AVX__
	((N==2)||(N==3)||(N==4)) ||
#endif
#if defined(__SSE__) && __SSE__
	((N==2)||(N==4)) ||
#endif
	false
>
{ };

// has_vec_data<double>
template <unsigned N>
struct _has_vec_data<double, N>
 : meta::boolean_constant<
#if defined(__AVX__) && __AVX__
	((N==2)||(N==4)) ||
#endif
#if defined(__SSE2__) && __SSE2__
	(N==2) ||
#endif
	false
>
{ };
#endif // EAGINE_USE_SIMD

// data
template <typename T, unsigned N>
struct data
 : meta::conditional<
	_has_vec_data<T, N>::value,
	_vec_data<T, N>,
	_ary_data<T, N>
>::type
{
	typedef T value_type;
	static constexpr unsigned size = N;
};

// data_param
template <typename T, unsigned N>
struct data_param
 : meta::conditional<
	_has_vec_data<T, N>::value,
	_vec_data<T, N>,
	_ary_cref<T, N>
>::type
{ };

// param
template <typename Data>
struct param;

template <typename T, unsigned N>
struct param<data<T, N>>
 : data_param<T, N>
{ };

} // namespace vect
} // namespace eagine

#endif //include guard

