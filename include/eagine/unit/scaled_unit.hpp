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
namespace bits {

template <typename ScaledUnits, typename System>
struct _sc_unit_sc_hlp
{
	template <typename T>
	static constexpr inline T _adj(T v, bool inv)
	{
		return inv?1.0/v:v;
	}

	template <typename DimPow>
	static constexpr inline auto _one_dim_pow(DimPow)
	{
		typedef typename System::template base_unit<
			typename DimPow::dim
		>::type base_unit;

		typedef typename base_unit::scale base_scale;

		return _adj(
			bits::get_scale<
				ScaledUnits,
				base_unit,
				base_scale
			>::value,
			DimPow::pow::value < 0
		);
	}

	static constexpr double _prod(void)
	{
		return 1.0;
	}

	template <typename X, typename ... P>
	static constexpr auto _prod(X v, P ... p)
	{
		return v*_prod(p...);
	}
};

} // namespace bits

template <typename Dims, typename ScaledUnits, typename System>
struct scaled_unit
{
	typedef Dims dimension;
	typedef ScaledUnits scales;
	typedef System system;
	typedef scaled_unit type;

	struct scale
	{
		typedef scale type;

		template <typename ... DimPow>
		struct _hlp
		{
			typedef _hlp type;

			typedef bits::_sc_unit_sc_hlp<ScaledUnits, System>_base;

			static constexpr auto scale = _base::_prod(
				_base::_one_dim_pow(DimPow())...
			);
		};

		typedef typename bits::apply<_hlp, Dims>::type _hlp2;

		static constexpr auto value = _hlp2::scale;
	};
};


template <typename D1, typename D2, typename SU, typename S>
struct value_conv<scaled_unit<D1, SU, S>, unit<D2, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v*scaled_unit<D1, SU, S>::scale::value;
	}
};

template <typename D1, typename D2, typename SU, typename S>
struct value_conv<unit<D1, S>, scaled_unit<D2, SU, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v/scaled_unit<D2, SU, S>::scale::value;
	}
};

template <typename D1, typename D2, typename SU1, typename SU2, typename S>
struct value_conv<scaled_unit<D1, SU1, S>, scaled_unit<D2, SU2, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		return v;
	}
};

template <typename D, typename SU, typename S>
struct add_result<scaled_unit<D, SU, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename D, typename SU, typename S>
struct add_result<unit<D, S>, scaled_unit<D, SU, S>>
 : unit<D, S>
{ };

template <typename D, typename SU, typename S>
struct sub_result<scaled_unit<D, SU, S>, unit<D, S>>
 : unit<D, S>
{ };

template <typename D, typename SU, typename S>
struct sub_result<unit<D, S>, scaled_unit<D, SU, S>>
 : unit<D, S>
{ };

template <typename D1, typename D2, typename SU, typename S>
struct mul_result<scaled_unit<D1, SU, S>, unit<D2, S>>
 : unit<typename bits::plus<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename SU, typename S>
struct mul_result<unit<D1, S>, scaled_unit<D2, SU, S>>
 : unit<typename bits::plus<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename SU1, typename SU2, typename S>
struct mul_result<scaled_unit<D1, SU1, S>, scaled_unit<D2, SU2, S>>
 : scaled_unit<
	typename bits::plus<D1, D2>::type,
	typename bits::merge<SU1, SU2>::type,
	S
>
{ };

template <typename D1, typename D2, typename SU, typename S>
struct div_result<scaled_unit<D1, SU, S>, unit<D2, S>>
 : unit<typename bits::minus<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename SU, typename S>
struct div_result<unit<D1, S>, scaled_unit<D2, SU, S>>
 : unit<typename bits::minus<D1, D2>::type, S>
{ };

template <typename D1, typename D2, typename SU1, typename SU2, typename S>
struct div_result<scaled_unit<D1, SU1, S>, scaled_unit<D2, SU2, S>>
 : scaled_unit<
	typename bits::minus<D1, D2>::type,
	typename bits::merge<SU1, SU2>::type,
	S
>
{ };

} // namespace unit
} // namespace EAGine

#endif //include guard

