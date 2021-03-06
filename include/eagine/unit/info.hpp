/**
 *  @file eagine/unit/info.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_INFO_1308281038_HPP
#define EAGINE_UNIT_INFO_1308281038_HPP

#include <eagine/unit/fwd.hpp>
#include <eagine/unit/base_unit.hpp>
#include <eagine/unit/detail.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/string.hpp>
#include <eagine/meta/utf8.hpp>
#include <eagine/base/string.hpp>

namespace eagine {
namespace unit {

// pow_str
template <int Pow>
struct pow_str
 : meta::translate<
	typename meta::int_to_str<Pow>::type,
	meta::superscript
>
{ };

template <>
struct pow_str<1>
 : meta::empty_string
{ };

// info
template <>
struct info<bits::nil_t>
{
	typedef meta::empty_string name;
};

// info dimensions
template <typename H, typename T>
struct info<bits::dims<H, T>>
{
	template <typename ... DimPow>
	struct _name_hlp : meta::join<
		meta::string<char(0xC3),char(0x97)>,
		typename meta::concat<
			typename base::dim_info<
				typename DimPow::dim
			>::name,
			typename pow_str<DimPow::pow::value>::type
		>::type...
	>
	{ };
	typedef typename bits::apply<_name_hlp, bits::dims<H, T>>::type name;
};

// info<unit>
template <typename Dims, typename System>
struct info<unit<Dims, System>>
{
	template <typename ... DimPow>
	struct _name_hlp : meta::join<
		meta::string<char(0xC3),char(0x97)>,
		typename meta::concat<
			typename base::unit_info<
				typename System::template base_unit<
					typename DimPow::dim
				>::type
			>::name,
			typename pow_str<DimPow::pow::value>::type
		>::type...
	>
	{ };
	typedef typename bits::apply<_name_hlp, Dims>::type name;

	template <typename ... DimPow>
	struct _sym_hlp : meta::join<
		meta::string<'.'>,
		typename meta::concat<
			typename base::unit_info<
				typename System::template base_unit<
					typename DimPow::dim
				>::type
			>::symbol,
			typename pow_str<DimPow::pow::value>::type
		>::type...
	>
	{ };
	typedef typename bits::apply<_sym_hlp, Dims>::type symbol;
};

// info<scaled_unit>
template <typename Dims, typename UnitScales, typename System>
struct info<scaled_unit<Dims, UnitScales, System>>
{
	template <typename ... DimPow>
	struct _name_hlp : meta::join<
		meta::string<char(0xC3),char(0x97)>,
		typename meta::concat<
			typename base::unit_info<
				typename bits::get_dim_unit<
					UnitScales,
					typename DimPow::dim,
					typename System::template base_unit<
						typename DimPow::dim
					>::type
				>::type
			>::name,
			typename pow_str<DimPow::pow::value>::type
		>::type...
	>
	{ };
	typedef typename bits::apply<_name_hlp, Dims>::type name;

	template <typename ... DimPow>
	struct _sym_hlp : meta::join<
		meta::string<'.'>,
		typename meta::concat<
			typename base::unit_info<
				typename bits::get_dim_unit<
					UnitScales,
					typename DimPow::dim,
					typename System::template base_unit<
						typename DimPow::dim
					>::type
				>::type
			>::symbol,
			typename pow_str<DimPow::pow::value>::type
		>::type...
	>
	{ };
	typedef typename bits::apply<_sym_hlp, Dims>::type symbol;
};

// dimension_name(Dimension)
template <typename Dimension>
static inline typename meta::enable_if<
	is_dimension<Dimension>::value,
	eagine::base::cstrref
>::type dimension_name(const Dimension& = Dimension())
noexcept
{
	typedef typename info<Dimension>::name ctn;
	return eagine::base::cstrref(
		meta::c_str<ctn>::value,
		meta:: size<ctn>::value
	);
}

// quantity_name(Unit)
template <typename Unit>
static inline typename meta::enable_if<
	is_unit<Unit>::value,
	eagine::base::cstrref
>::type quantity_name(const Unit& = Unit())
noexcept
{
	typedef typename info<typename Unit::dimension>::name ctn;
	return eagine::base::cstrref(
		meta::c_str<ctn>::value,
		meta:: size<ctn>::value
	);
}

// quantity_name(quanity)
template <typename U, typename T>
static inline auto quantity_name(const quantity<U, T>&)
noexcept
{
	return quantity_name<U>();
}

// unit_name(Unit)
template <typename Unit>
static inline typename meta::enable_if<
	is_unit<Unit>::value,
	eagine::base::cstrref
>::type unit_name(const Unit& = Unit())
noexcept
{
	typedef typename info<Unit>::name ctn;
	return eagine::base::cstrref(
		meta::c_str<ctn>::value,
		meta:: size<ctn>::value
	);
}

// unit_symbol(Unit)
template <typename Unit>
static inline typename meta::enable_if<
	is_unit<Unit>::value,
	eagine::base::cstrref
>::type unit_symbol(const Unit& = Unit())
noexcept
{
	typedef typename info<Unit>::symbol cts;
	return eagine::base::cstrref(
		meta::c_str<cts>::value,
		meta:: size<cts>::value
	);
}

// unit_name(quantity)
template <typename U, typename T>
static inline auto unit_name(const quantity<U, T>&)
noexcept
{
	return unit_name<U>();
}

// unit_symbol(quantity)
template <typename U, typename T>
static inline auto unit_symbol(const quantity<U, T>&)
noexcept
{
	return unit_symbol<U>();
}

} // namespace unit
} // namespace eagine

#endif //include guard

