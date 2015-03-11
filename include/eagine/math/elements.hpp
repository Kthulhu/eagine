/**
 *  @file eagine/math/elements.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_ELEMENTS_1308281038_HPP
#define EAGINE_MATH_ELEMENTS_1308281038_HPP

#include <eagine/math/vector.hpp>
#include <eagine/math/matrix.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/identity.hpp>

namespace eagine {
namespace math {

// element_type
template <typename X>
struct element_type;

// element_type<vector>
template <typename T, unsigned N>
struct element_type<vector<T,N>>
 : meta::identity<T>
{ };

// element_type<matrix>
template <typename T, unsigned R, unsigned C, bool RM>
struct element_type<matrix<T,R,C,RM>>
 : meta::identity<T>
{ };

// element_count
template <typename X>
struct element_count;

// element_count<vector>
template <typename T, unsigned N>
struct element_count<vector<T,N>>
 : meta::integral_constant<unsigned, N>
{ };

// element_count<matrix>
template <typename T, unsigned R, unsigned C, bool RM>
struct element_count<matrix<T,R,C,RM>>
 : meta::integral_constant<unsigned, R*C>
{ };

// data_elements
template <typename T, unsigned N, bool Fast>
struct data_elements;

// data_elements (fast)
template <typename T, unsigned N>
struct data_elements<T, N, true>
{
	const T* _e;
};

// data_elements (safe)
template <typename T, unsigned N>
struct data_elements<T, N,false>
{
	const T _e[N];
};

template <typename X, typename T, unsigned N>
struct data_elements_reintrpr_hlp
 : meta::boolean_constant<
	meta::is_pod<decltype(X::_v)>::value &&
	meta::is_pod<const T[N]>::value &&
	(sizeof(decltype(X::_v)) == sizeof(const T[N])) &&
	(alignof(decltype(X::_v)) == alignof(const T[N]))
>
{ };

// data_elements_reinterpretable trait
template <typename X>
struct data_elements_reinterpretable
 : data_elements_reintrpr_hlp<
	X,
	typename element_type<X>::type,
	element_count<X>::value
>
{ };

// get_elem(vector)
template <unsigned E, typename T, unsigned N>
static constexpr inline
typename meta::enable_if<(E<N), T>::type
get_elem(const vector<T,N>& v)
{
	return v._v[E];
}

// get_elem(matrix) (Row-major)
template <unsigned E, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(E<R*C), T>::type
get_elem(const matrix<T,R,C, true>& m)
{
	return m._v[E/C][E%C];
}

// get_elem(matrix) (Column-major)
template <unsigned E, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(E<R*C), T>::type
get_elem(const matrix<T,R,C,false>& m)
{
	return m._v[E/R][E%R];
}

// data(data_elements)
template <typename T, unsigned N, bool F>
static constexpr inline 
const T* data(const data_elements<T,N,F>& me)
{
	return me._e;
}

// size(data_elements)
template <typename T, unsigned N, bool F>
static constexpr inline
unsigned size(const data_elements<T,N,F>&)
{
	return N;
}

// elements(X) (fast)
template <typename X>
static constexpr inline
typename meta::enable_if<
	data_elements_reinterpretable<X>::value,
	data_elements<
		typename element_type<X>::type,
		element_count<X>::value,
		true
	>
>::type elements(const X& x)
{
	return {reinterpret_cast<const typename element_type<X>::type*>(&x._v)};
}

// elements_copy(X) (safe)
template <typename X, unsigned ... I>
static constexpr inline
data_elements<
	typename element_type<X>::type,
	element_count<X>::value,
	false
>
elements_copy(const X& x, meta::integer_sequence<unsigned, I...>)
{
	return {{get_elem<I>(x)...}};
}

// elements(X) (safe)
template <typename X>
static constexpr inline
typename meta::enable_if<
	!data_elements_reinterpretable<X>::value,
	data_elements<
		typename element_type<X>::type,
		element_count<X>::value,
		false
	>
>::type elements(const X& x)
{
	typedef typename meta::make_integer_sequence<
		unsigned, element_count<X>::value
	>::type is;
	return elements_copy(x, is());
}

} // namespace math
} // namespace eagine

#endif //include guard

