/**
 *  @file eagine/base/repeated.hpp
 *  @brief Range repeating the same element n-times
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_REPEATED_1308281038_HPP
#define EAGINE_BASE_REPEATED_1308281038_HPP

#include <eagine/base/iterator.hpp>

namespace eagine {
namespace base {

template <typename T>
class repeated
{
private:
	T _v;
	std::size_t _n;
public:
	template <typename P>
	repeated(P&& v, std::size_t n = 1)
	 : _v(std::forward<P>(v))
	 , _n(n)
	{ }

	typedef T value_type;
	typedef std::size_t size_type;
	typedef const T& reference;
	typedef const T& const_reference;

	bool empty(void) const
	{
		return _n == 0;
	}

	std::size_t size(void) const
	{
		return _n;
	}

	void clear(void)
	{
		_n = 0;
	}

	void resize(std::size_t n)
	{
		_n = n;
	}

	const T& at(std::size_t i) const
	noexcept
	{
		assert(i < size());
		return _v;
	}

	const T& operator[] (std::size_t i) const
	noexcept
	{
		return at(i);
	}

	typedef ras_iterator<const repeated<T>> iterator;
	typedef ras_iterator<const repeated<T>> const_iterator;

	iterator begin(void) const
	noexcept
	{
		return iterator(*this, 0);
	}

	iterator end(void) const
	noexcept
	{
		return iterator(*this, size());
	}
};

template <typename T>
inline
repeated<T> repeat(T&& v, std::size_t n)
{
	return repeated<T>(v, n);
}

} // namespace base
} // namespace eagine

#endif //include guard

