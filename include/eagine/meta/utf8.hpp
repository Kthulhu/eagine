/**
 *  @file eagine/meta/utf8.hpp
 *  @brief The compile-time utf8 tools.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_UTF8_1308281038_HPP
#define EAGINE_META_UTF8_1308281038_HPP

#include <eagine/meta/string.hpp>

namespace EAGine {
namespace meta {

template <typename String, template <char> class Transf>
struct translate;

template <char ... C, template <char> class Transf>
struct translate<string<C...>, Transf>
 : concat<Transf<C>...>
{ };

template <char C>
struct superscript;

template <>
struct superscript<'i'>
 : string<char(0xE2),char(0x81),char(0xB1)>
{ };

template <>
struct superscript<'n'>
 : string<char(0xE2),char(0x81),char(0xBF)>
{ };

template <>
struct superscript<'+'>
 : string<char(0xE2),char(0x81),char(0xBA)>
{ };

template <>
struct superscript<'-'>
 : string<char(0xE2),char(0x81),char(0xBB)>
{ };

template <>
struct superscript<'='>
 : string<char(0xE2),char(0x81),char(0xBC)>
{ };

template <>
struct superscript<'('>
 : string<char(0xE2),char(0x81),char(0xBD)>
{ };

template <>
struct superscript<')'>
 : string<char(0xE2),char(0x81),char(0xBE)>
{ };

template <>
struct superscript<'0'>
 : string<char(0xE2),char(0x81),char(0xB0)>
{ };

template <>
struct superscript<'1'>
 : string<char(0xC2),char(0xB9)>
{ };

template <>
struct superscript<'2'>
 : string<char(0xC2),char(0xB2)>
{ };

template <>
struct superscript<'3'>
 : string<char(0xC2),char(0xB3)>
{ };

template <>
struct superscript<'4'>
 : string<char(0xE2),char(0x82),char(0x84)>
{ };

template <>
struct superscript<'5'>
 : string<char(0xE2),char(0x82),char(0x85)>
{ };

template <>
struct superscript<'6'>
 : string<char(0xE2),char(0x82),char(0x86)>
{ };

template <>
struct superscript<'7'>
 : string<char(0xE2),char(0x82),char(0x87)>
{ };

template <>
struct superscript<'8'>
 : string<char(0xE2),char(0x82),char(0x88)>
{ };

template <>
struct superscript<'9'>
 : string<char(0xE2),char(0x82),char(0x89)>
{ };

} // namespace meta
} // namespace EAGine

#endif //include guard

