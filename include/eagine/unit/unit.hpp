/**
 *  @file eagine/unit/unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_UNIT_1308281038_HPP
#define EAGINE_UNIT_UNIT_1308281038_HPP

#include <eagine/unit/fwd.hpp>
#include <eagine/unit/detail.hpp>

namespace EAGine {
namespace unit {

template <typename Dims, typename System>
struct unit
{
	typedef Dims dimension;
	typedef System system;
	typedef scales::one scale;
	typedef unit type;
};

// value conv
template <typename D1, typename D2, typename S>
struct value_conv<unit<D1, S>, unit<D2, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v;
	}
};

// add_result
template <typename D, typename S>
struct add_result<unit<D, S>, unit<D, S>>
 : unit<D, S>
{ };

// sub_result
template <typename D, typename S>
struct sub_result<unit<D, S>, unit<D, S>>
 : unit<D, S>
{ };

// mul_result
template <typename D1, typename D2, typename S>
struct mul_result<unit<D1, S>, unit<D2, S>>
 : unit<typename bits::dim_add<D1, D2>::type, S>
{ };

// div_result
template <typename D1, typename D2, typename S>
struct div_result<unit<D1, S>, unit<D2, S>>
 : unit<typename bits::dim_sub<D1, D2>::type, S>
{ };

// addition
template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename add_result<U1, U2>::type
>::type operator + (U1, U2);

// subtraction
template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename sub_result<U1, U2>::type
>::type operator - (U1, U2);

// multiplication
template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename mul_result<U1, U2>::type
>::type operator * (U1, U2);

// division
template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename div_result<U1, U2>::type
>::type operator / (U1, U2);

} // namespace unit
} // namespace EAGine

#endif //include guard

