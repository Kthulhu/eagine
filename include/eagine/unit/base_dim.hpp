/**
 *  @file eagine/unit/base_dim.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_BASE_DIM_1308281038_HPP
#define EAGINE_UNIT_BASE_DIM_1308281038_HPP

#include <eagine/meta/int_const.hpp>
#include <eagine/meta/string.hpp>
#include <eagine/unit/scales.hpp>

namespace eagine {
namespace unit {
namespace base {

template <typename Derived>
struct dimension
{
	typedef Derived type;
};

struct angle       : dimension<angle> { };
struct solid_angle : dimension<solid_angle> { };

struct length : dimension<length> { };
struct mass   : dimension<mass> { };
struct time   : dimension<time> { };

struct temperature         : dimension<temperature> { };
struct electric_current    : dimension<electric_current> { };
struct number_of_cycles    : dimension<number_of_cycles> { };
struct number_of_decays    : dimension<number_of_decays> { };
struct luminous_intensity  : dimension<luminous_intensity> { };
struct amount_of_substance : dimension<amount_of_substance> { };

template <typename Dimension>
struct dim_num;

template <> struct dim_num<angle>  : meta::int_constant<0>{ };
template <> struct dim_num<mass>   : meta::int_constant<1> { };
template <> struct dim_num<length> : meta::int_constant<2> { };
template <> struct dim_num<time>   : meta::int_constant<3> { };

template <> struct dim_num<temperature>
 : meta::int_constant<4>
{ };

template <> struct dim_num<electric_current>
 : meta::int_constant<5>
{ };

template <> struct dim_num<number_of_cycles>
 : meta::int_constant<6>
{ };

template <> struct dim_num<number_of_decays>
 : meta::int_constant<7>
{ };

template <> struct dim_num<luminous_intensity>
 : meta::int_constant<8>
{ };

template <> struct dim_num<amount_of_substance>
 : meta::int_constant<9>
{ };

template <> struct dim_num<solid_angle>
 : meta::int_constant<10>
{ };
  
template <typename Dimension>
struct dim_info;

template <>
struct dim_info<angle>
{
	typedef meta::string<'a','n','g','l','e'> name;
};

template <>
struct dim_info<solid_angle>
{
	typedef meta::string<
		's','o','l','i','d',' ',
		'a','n','g','l','e'
	> name;
};

template <>
struct dim_info<mass>
{
	typedef meta::string<'m','a','s','s'> name;
};

template <>
struct dim_info<length>
{
	typedef meta::string<'l','e','n','g','t','h'> name;
};

template <>
struct dim_info<time>
{
	typedef meta::string<'t','i','m','e'> name;
};

template <>
struct dim_info<temperature>
{
	typedef meta::string<'t','e','m','p','e','r','a','t','u','r','e'> name;
};

template <>
struct dim_info<electric_current>
{
	typedef meta::string<
		'e','l','e','c','t','r','i','c',' ',
		'c','u','r','r','e','n','t'
	> name;
};

template <>
struct dim_info<number_of_cycles>
{
	typedef meta::string<
		'n','u','m','b','e','r',
		' ','o','f',' ',
		'c','y','c','l','e','s'
	> name;
};

template <>
struct dim_info<number_of_decays>
{
	typedef meta::string<
		'n','u','m','b','e','r',
		' ','o','f',' ',
		'd','e','c','a','y','s'
	> name;
};

template <>
struct dim_info<luminous_intensity>
{
	typedef meta::string<
		'l','u','m','i','n','o','u','s',' ',
		'i','n','t','e','n','s','i','t','y'
	> name;
};

template <>
struct dim_info<amount_of_substance>
{
	typedef meta::string<
		'a','m','o','u','n','t',
		' ','o','f',' ',
		's','u','b','s','t','a','n','c','e'
	> name;
};

} // namespace base
} // namespace unit
} // namespace eagine

#endif //include guard

