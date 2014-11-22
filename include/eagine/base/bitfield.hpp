/**
 *  @file eagine/base/bitfield.hpp
 *  @brief Strongly typed bitfield.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_BITFIELD_1308281038_HPP
#define EAGINE_BASE_BITFIELD_1308281038_HPP

#include <initializer_list>
#include <type_traits>

namespace eagine {
namespace base {

template <typename Bits>
class bitfield
{
public:
	typedef typename std::underlying_type<Bits>::type type;
private:
	type _bits;
public:
	constexpr bitfield(void)
	noexcept
	 : _bits(type(0))
	{ }

	explicit constexpr bitfield(type initial)
	noexcept
	 : _bits(initial)
	{ }

	constexpr bitfield(Bits b)
	noexcept
	 : _bits(type(b))
	{ }

	constexpr bitfield(Bits b1, Bits b2)
	noexcept
	 : _bits(type(b1)|type(b2))
	{ }

	bitfield(std::initializer_list<Bits> initial)
	noexcept
	 : _bits(type(0))
	{
		for(Bits bit : initial)
		{
			set(bit);
		}
	}

	friend constexpr bitfield operator | (bitfield bf, Bits bit)
	noexcept
	{
		return bitfield(bf._bits | type(bit));
	}

	bool is_set(Bits bit) const
	noexcept
	{
		return (_bits & type(bit)) == type(bit);
	}

	struct _f_and_b
	{
		const bitfield& _f;
		bool _b;

		_f_and_b(const bitfield& f, bool b)
		noexcept
		 : _f(f)
		 , _b(b)
		{ }

		explicit operator bool (void) const
		noexcept
		{
			return _b;
		}

		_f_and_b operator & (Bits bit) const
		noexcept
		{
			return _f_and_b(_f, _b && _f.is_set(bit));
		}
	};

	_f_and_b operator & (Bits bit) const
	noexcept
	{
		return _f_and_b(*this, is_set(bit));
	}

	bitfield& set(Bits bit)
	noexcept
	{
		_bits |= type(bit);
		return *this;
	}

	bitfield& operator << (Bits bit)
	noexcept
	{
		return set(bit);
	}

	bitfield& clear(Bits bit)
	noexcept
	{
		_bits &= ~type(bit);
		return *this;
	}

	bitfield& operator >> (Bits bit)
	noexcept
	{
		return clear(bit);
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

