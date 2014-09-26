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
	static constexpr inline T _pow(T val, int exp)
	{
		return (exp == 0)?1:
			(exp > 0)?
				_pow(val, exp-1)*val:
				_pow(val, exp+1)/val;
	}

	template <typename DimPow>
	static constexpr inline auto _one_dim_pow(DimPow)
	{
		typedef typename System::template base_unit<
			typename DimPow::dim
		>::type base_unit;

		typedef typename base_unit::scale base_scale;

		return _pow(
			bits::get_scale<
				ScaledUnits,
				base_unit,
				base_scale
			>::value,
			DimPow::pow::value
		);
	}

	static constexpr int _prod(void)
	{
		return 1;
	}

	template <typename X, typename ... P>
	static constexpr auto _prod(X v, P ... p)
	{
		return v*_prod(p...);
	}
};

} // namespace bits

template <typename Dims, typename ScaledUnits, typename System>
struct scaled_unit_scale
{
	typedef scaled_unit_scale type;

	template <typename ... DimPow>
	struct _hlp
	{
		typedef _hlp type;

		typedef bits::_sc_unit_sc_hlp<ScaledUnits, System> _base;

		static constexpr auto scale = _base::_prod(
			_base::_one_dim_pow(DimPow())...
		);
	};

	typedef typename bits::apply<_hlp, Dims>::type _hlp2;

	static constexpr auto value = _hlp2::scale;
};

template <typename Dims, typename ScaledUnits, typename System>
struct scaled_unit
{
	typedef Dims dimension_type;
	typedef ScaledUnits scales;
	typedef System system;
	typedef scaled_unit type;
};


template <typename D1, typename D2, typename SU, typename S>
struct value_conv<scaled_unit<D1, SU, S>, unit<D2, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		typedef scaled_unit_scale<D1, SU, S> scale;
		return v*scale::value;
	}
};

template <typename D1, typename D2, typename SU, typename S>
struct value_conv<unit<D1, S>, scaled_unit<D2, SU, S>>
{
	typedef value_conv type;

	template <typename T>
	static constexpr inline T apply(T v)
	{
		typedef scaled_unit_scale<D2, SU, S> scale;
		return v/scale::value;
	}
};

} // namespace unit
} // namespace EAGine

#endif //include guard

