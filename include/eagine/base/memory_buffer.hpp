/**
 *  @file eagine/base/memory_buffer.hpp
 *  @brief Resizable memory buffer with exclusive ownership.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_MEMORY_BUFFER_1408161723_HPP
#define EAGINE_BASE_MEMORY_BUFFER_1408161723_HPP

#include <eagine/base/memory_block.hpp>
#include <cstdlib>

namespace eagine {
namespace base {

class memory_buffer
{
private:
	void* _addr;
	std::size_t _size;
public:
	memory_buffer(void)
	noexcept
	 : _addr(nullptr)
	 , _size(0)
	{ }

	memory_buffer(std::size_t init_size)
	noexcept
	 : _addr(::std::malloc(init_size))
	 , _size(_addr?init_size:0)
	{ }

	memory_buffer(const memory_buffer&) = delete;

	memory_buffer(memory_buffer&& tmp)
	noexcept
	 : _addr(tmp._addr)
	 , _size(tmp._size)
	{
		tmp._addr = nullptr;
		tmp._size = 0;
	}

	~memory_buffer(void)
	noexcept
	{
		if(_addr)
		{
			::std::free(_addr);
		}
	}

	memory_buffer& resize(std::size_t new_size)
	noexcept
	{
		if(new_size != 0)
		{
			_addr = ::std::realloc(_addr, new_size);
			_size = _addr?new_size:0;
		}
		else
		{
			::std::free(_addr);
			_addr = nullptr;
			_size = 0;
		}
		return *this;
	}

	std::size_t size(void) const
	noexcept
	{
		assert((_addr == nullptr) == (_size == 0));
		return _size;
	}

	bool empty(void) const
	noexcept
	{
		return size() == 0;
	}

	explicit operator bool (void) const
	noexcept
	{
		return !empty();
	}

	memory_block block(void)
	noexcept
	{
		return {_addr, _size};
	}

	const_memory_block block(void) const
	noexcept
	{
		return {_addr, _size};
	}

	operator memory_block(void)
	noexcept
	{
		return block();
	}

	operator const_memory_block(void) const
	noexcept
	{
		return block();
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

