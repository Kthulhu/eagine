/**
 *  @file eagine/base/memory_buffer.hpp
 *  @brief Resizable memory buffer with exclusive ownership.
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
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
 : public crtp_memory_range<memory_buffer, void, byte>
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

	void* addr(void)
	noexcept
	{
		return _addr;
	}

	const void* addr(void) const
	noexcept
	{
		return _addr;
	}

	std::size_t size(void) const
	noexcept
	{
		assert((_addr == nullptr) == (_size == 0));
		return _size;
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

