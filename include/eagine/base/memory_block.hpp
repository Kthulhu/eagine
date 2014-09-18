/**
 *  @file eagine/base/memory_block.hpp
 *  @brief Memory block.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_MEMORY_BLOCK_1408161723_HPP
#define EAGINE_BASE_MEMORY_BLOCK_1408161723_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/base/type.hpp>
#include <cstddef>
#include <cassert>

namespace EAGine {
namespace base {

template <typename T>
class typed_memory_range;

template <bool Const>
class basic_memory_block
{
private:
	typedef typename meta::conditional<
		Const,
		const void,
		void
	>::type T;

	typedef typename meta::conditional<
		Const,
		const byte,
		byte
	>::type B;

	T* _addr;
	std::size_t _size;
public:
	basic_memory_block(void)
	 : _addr(nullptr)
	 , _size(0)
	{ }

	basic_memory_block(T* addr_, std::size_t size_)
	 : _addr(addr_)
	 , _size(size_)
	{ }

	basic_memory_block(
		const basic_memory_block<false>& that
	): _addr(that.addr())
	 , _size(that.size())
	{ }

	explicit operator bool (void) const
	{
		return (_addr != nullptr) && (_size != 0);
	}

	T* addr(void) const
	{
		return _addr;
	}

	std::size_t size(void) const
	{
		return _size;
	}

	basic_memory_block slice(std::size_t begin, std::size_t size_) const
	{
		assert(begin+size_ <= _size);
		return basic_memory_block(
			(T*)(((B*)_addr)+begin),
			size
		);
	}

	basic_memory_block slice(std::size_t begin) const
	{
		assert(begin <= _size);
		return slice(begin, _size-begin);
	}
};

typedef basic_memory_block<false> memory_block;
typedef basic_memory_block<true > const_memory_block;

} // namespace base
} // namespace EAGine

#endif //include guard

