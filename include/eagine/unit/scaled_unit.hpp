/**
 *  @file eagine/unit/scaled_unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_SCALED_UNIT_1308281038_HPP
#define EAGINE_UNIT_SCALED_UNIT_1308281038_HPP

#include <eagine/unit/base_scaled_unit.hpp>
#include <eagine/unit/unit.hpp>
#include <cmath>

namespace EAGine {
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
		struct _hlp
		{
			typedef _hlp type;

			typedef bits::_sc_unit_sc_hlp<Scales, System>_base;

			static constexpr auto scale = _base::_prod(
				_base::_one_dim_pow(DimPow())...
			);
		};

		typedef typename bits::apply<_hlp, Dims>::type _hlp2;

		static constexpr auto value = _hlp2::scale;
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
		return v*scaled_unit<D1, US, S>::scale::value;
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

template <typename D, typename US, typename S>
struct add_result<scaled_unit<D, US, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename D, typename US, typename S>
struct add_result<unit<D, S>, scaled_unit<D, US, S>>
 : unit<D, S>
{ };

template <typename D, typename US, typename S>
struct sub_result<scaled_unit<D, US, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename D, typename US, typename S>
struct sub_result<unit<D, S>, scaled_unit<D, US, S>>
 : unit<D, S>
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
} // namespace EAGine

#endif //include guard

