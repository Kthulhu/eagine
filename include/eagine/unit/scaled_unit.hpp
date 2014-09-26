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

	template <typename ... DimPow>
	struct _hlp
	{
		typedef _hlp type;

		template <typename DP>
		static constexpr inline auto _single(DP)
		{
			typedef typename S::template base_unit<
				typename DP::dim
			>::type BU;
			typedef typename BU::scale BS;

			using std::pow;
			
			return pow(
				bits::get_scale<SU, BU, BS>::value,
				DP::pow::value
			);
		}

		static constexpr int prod(void)
		{
			return 1;
		}

		template <typename X, typename ... P>
		static constexpr auto prod(X v, P ... p)
		{
			return v*prod(p...);
		}

		template <typename T>
		static constexpr auto scale(T v)
		{
			return v*prod(_single(DimPow())...);
		}
	};

	template <typename T>
	static constexpr inline T apply(T v)
	{
		typedef typename bits::apply<_hlp, D1>::type h;
		return h::scale(v);
	}
};

} // namespace unit
} // namespace EAGine

#endif //include guard

