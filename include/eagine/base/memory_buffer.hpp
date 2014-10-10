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

namespace EAGine {
namespace base {

class memory_buffer
{
private:
	void* _addr;
	std::size_t _size;
public:
	memory_buffer(void)
	 : _addr(nullptr)
	 , _size(0)
	{ }

	memory_buffer(std::size_t init_size)
	 : _addr(::std::malloc(init_size))
	 , _size(_addr?init_size:0)
	{ }

	memory_buffer(const memory_buffer&) = delete;

	memory_buffer(memory_buffer&& tmp)
	 : _addr(tmp._addr)
	 , _size(tmp._size)
	{
		tmp._addr = nullptr;
		tmp._size = 0;
	}

	~memory_buffer(void)
	{
		if(_addr)
		{
			::std::free(_addr);
		}
	}

	memory_buffer& resize(std::size_t new_size)
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
	{
		assert((_addr == nullptr) == (_size == 0));
		return _size;
	}

	bool empty(void) const
	{
		return size() == 0;
	}

	memory_block block(void)
	{
		return {_addr, _size};
	}

	const_memory_block block(void) const
	{
		return {_addr, _size};
	}

	operator memory_block(void)
	{
		return block();
	}

	operator const_memory_block(void) const
	{
		return block();
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard
