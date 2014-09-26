/**
 *  @file eagine/unit/unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_UNIT_1308281038_HPP
#define EAGINE_UNIT_UNIT_1308281038_HPP

#include <eagine/unit/detail.hpp>

namespace EAGine {
namespace unit {

struct rmks;

template <typename Dims, typename System = rmks>
struct unit
{
	typedef Dims dimension_type;
	typedef System system;
	typedef unit type;
};

template <typename U1, typename U2>
struct add_result;

template <typename D, typename S>
struct add_result<unit<D, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename U1, typename U2>
struct sub_result;

template <typename D, typename S>
struct sub_result<unit<D, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename U1, typename U2>
struct mul_result;

template <typename D1, typename D2, typename S>
struct mul_result<unit<D1, S>, unit<D2, S>>
 : unit<typename bits::plus<D1, D2>::type, S>
{ };

template <typename U1, typename U2>
struct div_result;

template <typename D1, typename D2, typename S>
struct div_result<unit<D1, S>, unit<D2, S>>
 : unit<typename bits::minus<D1, D2>::type, S>
{ };

template <typename U1, typename U2>
static constexpr inline
auto operator * (U1, U2)
{
	return typename mul_result<U1, U2>::type();
}

template <typename U1, typename U2>
static constexpr inline
auto operator / (U1, U2)
{
	return typename div_result<U1, U2>::type();
}

// value conv
template <typename UnitFrom, typename UnitTo>
struct value_conv
{
	static_assert(
		!meta::is_same<UnitFrom, UnitTo>::value,
		"Incompatible unit conversion"
	);

	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v;
	}
};

template <typename D, typename S>
struct value_conv<unit<D, S>, unit<D, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v;
	}
};

} // namespace unit
} // namespace EAGine

#endif //include guard

