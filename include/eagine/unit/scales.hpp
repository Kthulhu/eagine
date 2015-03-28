/**
 *  @file eagine/unit/scales.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SCALES_1308281038_HPP
#define EAGINE_UNIT_SCALES_1308281038_HPP

#include <eagine/meta/string.hpp>
#include <cmath>

namespace eagine {
namespace unit {
namespace scales {

template <typename X>
struct scale_info;

struct one
{
	typedef one type;

	static constexpr int value = 1;
};

template <>
struct scale_info<one>
{
	typedef meta::empty_string name;
	typedef meta::empty_string symbol;
};

template <int Num, int Den>
struct rational
{
	typedef rational type;

	struct _impl
	{
		template <typename T>
		friend constexpr inline
		auto operator*(T v, _impl)
		noexcept
		{
			return (v*Num)/Den;
		}

		template <typename T>
		friend constexpr inline
		auto operator/(T v, _impl)
		noexcept
		{
			return (v*Den)/Num;
		}
	};
	static constexpr _impl value = {};
};

typedef rational<1, 1000000000> nano;

template <>
struct scale_info<nano>
{
	typedef meta::string<'n','a','n','o'> name;
	typedef meta::string<'n'> symbol;
};

typedef rational<1, 1000000> micro;

template <>
struct scale_info<micro>
{
	typedef meta::string<'m','i','c','r','o'> name;
	typedef meta::string<char(0xCE), char(0xBC)> symbol;
};

typedef rational<1, 1000> milli;

template <>
struct scale_info<milli>
{
	typedef meta::string<'m','i','l','l','i'> name;
	typedef meta::string<'m'> symbol;
};

typedef rational<1, 100> centi;

template <>
struct scale_info<centi>
{
	typedef meta::string<'c','e','n','t','i'> name;
	typedef meta::string<'c'> symbol;
};

typedef rational<1, 10> deci;

template <>
struct scale_info<deci>
{
	typedef meta::string<'d','e','c','i'> name;
	typedef meta::string<'d'> symbol;
};

typedef rational<10, 1> deca;

template <>
struct scale_info<deca>
{
	typedef meta::string<'d','e','c','a'> name;
	typedef meta::string<'d','c'> symbol;
};

typedef rational<100, 1> hecto;

template <>
struct scale_info<hecto>
{
	typedef meta::string<'h','e','c','t','o'> name;
	typedef meta::string<'h'> symbol;
};

typedef rational<1000, 1> kilo;

template <>
struct scale_info<kilo>
{
	typedef meta::string<'k','i','l','o'> name;
	typedef meta::string<'k'> symbol;
};

typedef rational<1000000, 1> mega;

template <>
struct scale_info<mega>
{
	typedef meta::string<'m','e','g','a'> name;
	typedef meta::string<'M'> symbol;
};

typedef rational<1000000000, 1> giga;

template <>
struct scale_info<giga>
{
	typedef meta::string<'g','i','g','a'> name;
	typedef meta::string<'G'> symbol;
};

struct pi
{
	typedef pi type;

	struct _impl
	{
		template <typename T>
		friend constexpr inline
		auto operator*(T v,_impl)
		noexcept
		{
			return v*M_PI;
		}

		template <typename T>
		friend constexpr inline
		auto operator/(T v,_impl)
		noexcept
		{
			return v/M_PI;
		}
	};
	static constexpr _impl value = {};
};

template <>
struct scale_info<pi>
{
	typedef meta::string<char(0xCF), char(0x80)> name;
	typedef meta::string<char(0xCF), char(0x80)> symbol;
};

template <typename S>
struct inverted
{
	typedef inverted type;

	struct _impl
	{
		template <typename T>
		friend constexpr inline
		auto operator*(T v,_impl)
		noexcept
		{
			return v/S::value;
		}

		template <typename T>
		friend constexpr inline
		auto operator/(T v,_impl)
		noexcept
		{
			return v*S::value;
		}
	};

	static constexpr _impl value = {};
};

template <typename S1, typename S2>
struct multiplied
{
	typedef multiplied type;

	struct _impl
	{
		template <typename T>
		friend constexpr inline
		auto operator*(T v,_impl)
		noexcept
		{
			return (v*S1::value)*S2::value;
		}

		template <typename T>
		friend constexpr inline
		auto operator/(T v,_impl)
		noexcept
		{
			return (v/S1::value)/S2::value;
		}
	};

	static constexpr _impl value = {};
};

template <typename S1, typename S2>
struct divided
{
	typedef divided type;

	struct _impl
	{
		template <typename T>
		friend constexpr inline
		auto operator*(T v,_impl)
		noexcept
		{
			return (v*S1::value)/S2::value;
		}

		template <typename T>
		friend constexpr inline
		auto operator/(T v,_impl)
		noexcept
		{
			return (v/S1::value)*S2::value;
		}
	};

	static constexpr _impl value = {};
};

} // namespace scales
} // namespace unit
} // namespace eagine

#endif //include guard

