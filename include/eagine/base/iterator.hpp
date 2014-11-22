/**
 *  @file eagine/base/iterator.hpp
 *  @brief Iterator templates
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ITERATOR_1308281038_HPP
#define EAGINE_BASE_ITERATOR_1308281038_HPP

#include <cstddef>
#include <cassert>

namespace eagine {
namespace base {

template <typename RASequence>
class ras_iterator
{
private:
	std::size_t _pos;
	RASequence* _psq;

	RASequence& _seq(void) const
	noexcept
	{
		assert(_psq);
		return *_psq;
	}

	template <typename S>
	static bool _valid_pos(
		std::size_t pos,
		const S* ps,
		std::size_t (S::*)(void) const = &S::size
	) noexcept
	{
		assert(ps);
		return pos < ps->size();
	}

	static bool _valid_pos(std::size_t, ...)
	noexcept
	{
		return true;
	}

	bool _valid_pos(void) const
	noexcept
	{
		return _valid_pos(_pos, _psq);
	}
public:
	ras_iterator(RASequence& seq, std::size_t pos)
	noexcept
	 : _pos(pos)
	 , _psq(&seq)
	{ }

	typedef typename RASequence::value_type value_type;
	typedef typename RASequence::reference reference;

	friend bool operator == (const ras_iterator& a, const ras_iterator& b)
	noexcept
	{
		assert(a._psq == b._psq);
		return a._pos == b._pos;
	}

	friend bool operator != (const ras_iterator& a, const ras_iterator& b)
	noexcept
	{
		assert(a._psq == b._psq);
		return a._pos != b._pos;
	}

	friend bool operator <  (const ras_iterator& a, const ras_iterator& b)
	noexcept
	{
		assert(a._psq == b._psq);
		return a._pos <  b._pos;
	}

	friend bool operator <= (const ras_iterator& a, const ras_iterator& b)
	noexcept
	{
		assert(a._psq == b._psq);
		return a._pos <= b._pos;
	}

	friend bool operator >  (const ras_iterator& a, const ras_iterator& b)
	noexcept
	{
		assert(a._psq == b._psq);
		return a._pos >  b._pos;
	}

	friend bool operator >= (const ras_iterator& a, const ras_iterator& b)
	noexcept
	{
		assert(a._psq == b._psq);
		return a._pos >= b._pos;
	}

	reference operator * (void)
	noexcept
	{
		assert(_valid_pos());
		return _seq()[_pos];
	}

	reference operator * (void) const
	noexcept
	{
		assert(_valid_pos());
		return _seq()[_pos];
	}

	ras_iterator& operator ++ (void)
	noexcept
	{
		assert(_valid_pos());
		++_pos;
		return *this;
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

