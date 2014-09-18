/**
 *  @file eagine/base/bitfield.hpp
 *  @brief Strongly typed bitfield.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_BITFIELD_1308281038_HPP
#define EAGINE_BASE_BITFIELD_1308281038_HPP

#include <initializer_list>

namespace EAGine {
namespace base {

template <typename Bits>
class bitfield
{
public:
	typedef typename std::underlying_type<Bits>::type type;
private:
	type _bits;
public:
	bitfield(void)
	 : _bits(type(0))
	{ }

	explicit bitfield(type initial)
	 : _bits(initial)
	{ }

	bitfield(Bits b)
	 : _bits(type(b))
	{ }

	bitfield(Bits b1, Bits b2)
	 : _bits(type(b1)|type(b2))
	{ }

	bitfield(std::initializer_list<Bits> initial)
	 : _bits(type(0))
	{
		for(Bits bit : initial)
		{
			set(bit);
		}
	}

	friend bitfield operator | (bitfield bf, Bits bit)
	{
		return bitfield(bf._bits | type(bit));
	}

	bool is_set(Bits bit) const
	{
		return (_bits & type(bit)) == type(bit);
	}

	struct _f_and_b
	{
		const bitfield& _f;
		bool _b;

		_f_and_b(const bitfield& f, bool b)
		 : _f(f)
		 , _b(b)
		{ }

		explicit operator bool (void) const
		{
			return _b;
		}

		_f_and_b operator & (Bits bit) const
		{
			return _f_and_b(_f, _b && _f.is_set(bit));
		}
	};

	_f_and_b operator & (Bits bit) const
	{
		return _f_and_b(*this, is_set(bit));
	}

	bitfield& set(Bits bit)
	{
		_bits |= type(bit);
		return *this;
	}

	bitfield& operator << (Bits bit)
	{
		return set(bit);
	}

	bitfield& clear(Bits bit)
	{
		_bits &= ~type(bit);
		return *this;
	}

	bitfield& operator >> (Bits bit)
	{
		return clear(bit);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

