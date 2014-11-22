/**
 *  @file eagine/base/indexed_array.hpp
 *  @brief Array of constant item with explicit indexing.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_INDEXED_ARRAY_1308281038_HPP
#define EAGINE_BASE_INDEXED_ARRAY_1308281038_HPP

#include <eagine/base/memory_range.hpp>
#include <eagine/base/type.hpp>
#include <cstddef>
#include <cassert>

namespace eagine {
namespace base {

template <typename T, typename I = std::uint32_t>
class indexed_array
{
private:
	typed_memory_range<const byte> _data;
	typed_memory_range<const I> _index;
public:
	indexed_array(
		const const_memory_block& data,
		const const_memory_block& index
	): _data(data)
	 , _index(index)
	{ }

	bool empty(void) const
	{
		return _index.size() == 0;
	}

	std::size_t size(void) const
	{
		return _index.size();
	}

	const T& at(std::size_t pos) const
	{
		assert(pos < _index.size());

		I offs = _index.at(pos);

		const void* addr = _data.begin()+offs;
		const T* ptr = static_cast<const T*>(addr);

		return *ptr;
	}

	class iterator
	{
	private:
		std::size_t  _pos;
		const indexed_array* _par;
	public:
		iterator(void)
		 : _pos(0)
		 , _par(nullptr)
		{ }

		iterator(std::size_t pos, const indexed_array& arr)
		 : _pos(pos)
		 , _par(&arr)
		{ }

		const T& operator * (void) const
		{
			assert(_par);
			assert(_pos < _par->size());
			return _par->at(_pos);
		}

		iterator& operator ++ (void)
		{
			++_pos;
			return *this;
		}

		friend bool operator == (const iterator& a, const iterator& b)
		{
			assert(a._par == b._par);
			return (a._pos == b._pos);
		}

		friend bool operator != (const iterator& a, const iterator& b)
		{
			assert(a._par == b._par);
			return (a._pos != b._pos);
		}
	};

	typedef iterator const_iterator;

	const_iterator begin(void) const
	{
		return const_iterator(0, *this);
	}

	const_iterator end(void) const
	{
		return const_iterator(size(), *this);
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

