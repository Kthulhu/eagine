/**
 *  @file eagine/unit/scaled_unit.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SCALED_UNIT_1308281038_HPP
#define EAGINE_UNIT_SCALED_UNIT_1308281038_HPP

#include <eagine/unit/dimension.hpp>
#include <eagine/unit/base_scaled_unit.hpp>
#include <eagine/unit/unit.hpp>
#include <cmath>

namespace eagine {
namespace unit {

template <typename Dims, typename Scales, typename System>
struct scaled_unit
{
	typedef Dims dimension;
	typedef Scales scales;
	typedef System system;
	typedef scaled_unit type;

	struct scale
	{
		typedef scale type;

		template <typename ... DimPow>
		struct _impl : bits::_sc_unit_sc_hlp<Scales, System>
		{
			typedef _impl type;

			template <typename T>
			friend constexpr inline
			auto operator * (T v, _impl i)
			noexcept
			{
				return i._hlp(+1, v, DimPow()...);
			}

			template <typename T>
			friend constexpr inline
			auto operator / (T v, _impl i)
			noexcept
			{
				return i._hlp(-1, v, DimPow()...);
			}
		};

		static constexpr typename bits::apply<
			_impl,
			Dims
		>::type value = {};
	};
};

template <typename BaseScaledUnit, typename System>
struct make_scaled_unit;

template <typename Scale, typename BaseUnit, typename System>
struct make_scaled_unit<base::scaled_unit<Scale, BaseUnit>, System>
 : scaled_unit<
	dimension<typename BaseUnit::dimension, 1>,
	typename bits::unit_scales<
		bits::uni_sca<BaseUnit, Scale>,
		bits::nil_t
	>::type,
	System
>
{ };

template <typename D1, typename D2, typename US, typename S>
struct value_conv<scaled_unit<D1, US, S>, unit<D2, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return T(v*scaled_unit<D1, US, S>::scale::value);
	}
};

template <typename D1, typename D2, typename US, typename S>
struct value_conv<unit<D1, S>, scaled_unit<D2, US, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v/scaled_unit<D1, US, S>::scale::value;
	}
};

template <typename D1, typename D2, typename US1, typename US2, typename S>
struct value_conv<scaled_unit<D1, US1, S>, scaled_unit<D2, US2, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v*
			scaled_unit<D1, US1, S>::scale::value/
			scaled_unit<D1, US2, S>::scale::value;
	}
};

template <typename D, typename S>
struct lit_result<unit<D, S>>
 : scaled_unit<D, bits::unit_scales<bits::nil_t, bits::nil_t>, S>
{ };

template <typename D, typename US, typename S>
struct lit_result<scaled_unit<D, US, S>>
 : scaled_unit<D, US, S>
{ };

template <typename D, typename US, typename S>
struct add_result<scaled_unit<D, US, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename D, typename US, typename S>
struct add_result<unit<D, S>, scaled_unit<D, US, S>>
 : unit<D, S>
{ };

template <typename D, typename US1, typename US2, typename S>
struct add_result<scaled_unit<D, US1, S>, scaled_unit<D, US2, S>>
 : scaled_unit<D, US1, S>
{ };

template <typename D, typename US, typename S>
struct sub_result<scaled_unit<D, US, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename D, typename US, typename S>
struct sub_result<unit<D, S>, scaled_unit<D, US, S>>
 : unit<D, S>
{ };

template <typename D, typename US1, typename US2, typename S>
struct sub_result<scaled_unit<D, US1, S>, scaled_unit<D, US2, S>>
 : scaled_unit<D, US1, S>
{ };

template <typename D1, typename D2, typename US, typename S>
struct mul_result<scaled_unit<D1, US, S>, unit<D2, S>>
 : unit<typename bits::dim_add<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename US, typename S>
struct mul_result<unit<D1, S>, scaled_unit<D2, US, S>>
 : unit<typename bits::dim_add<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename US1, typename US2, typename S>
struct mul_result<scaled_unit<D1, US1, S>, scaled_unit<D2, US2, S>>
 : scaled_unit<
	typename bits::dim_add<D1, D2>::type,
	typename bits::merge<US1, US2>::type,
	S
>
{ };

template <typename D1, typename D2, typename US, typename S>
struct div_result<scaled_unit<D1, US, S>, unit<D2, S>>
 : unit<typename bits::dim_sub<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename US, typename S>
struct div_result<unit<D1, S>, scaled_unit<D2, US, S>>
 : unit<typename bits::dim_sub<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename US1, typename US2, typename S>
struct div_result<scaled_unit<D1, US1, S>, scaled_unit<D2, US2, S>>
 : scaled_unit<
	typename bits::dim_sub<D1, D2>::type,
	typename bits::merge<US1, US2>::type,
	S
>
{ };

} // namespace unit
} // namespace eagine

#endif //include guard

