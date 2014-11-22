/**
 *  @file eagine/base/buffer_alloc.hpp
 *  @brief Buffer-backed byte allocator
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_BUFFER_ALLOC_1308281038_HPP
#define EAGINE_BASE_BUFFER_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/memory_buffer.hpp>

namespace eagine {
namespace base {

// allocator_backing_buffer
class allocator_backing_buffer
{
protected:
	memory_buffer _buffer;


	allocator_backing_buffer(std::size_t size)
	 : _buffer(size)
	{ }
public:
	allocator_backing_buffer(const allocator_backing_buffer&) = delete;
	allocator_backing_buffer(allocator_backing_buffer&&) = default;
};

// buffer_backed_byte_allocator
template <
	template <class> class ByteAllocTpl,
	typename Policy = default_byte_allocator_policy
>
class buffer_backed_byte_allocator
 : public allocator_backing_buffer
 , public ByteAllocTpl<Policy>
{
public:
	buffer_backed_byte_allocator(buffer_backed_byte_allocator&&) = default;

	template <typename ... P>
	buffer_backed_byte_allocator(std::size_t buf_size, P&& ... p)
	 : allocator_backing_buffer(buf_size)
	 , ByteAllocTpl<Policy>(
		allocator_backing_buffer::_buffer,
		std::forward<P>(p)...
	)
	{ }

	buffer_backed_byte_allocator* accomodate_self(void)
	noexcept
	{
		return this->accomodate_derived(*this);
	}

	void eject_self(void)
	noexcept override
	{
		this->eject_derived(*this);
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

