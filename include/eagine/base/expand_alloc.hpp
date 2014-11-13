/**
 *  @file eagine/base/expand_alloc.hpp
 *  @brief Buffer-backed byte allocator
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_EXPAND_ALLOC_1308281038_HPP
#define EAGINE_BASE_EXPAND_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/function.hpp>

namespace EAGine {
namespace base {

// expanding byte allocator
template <typename Policy = default_byte_allocator_policy>
class expanding_byte_allocator
 : public byte_allocator_impl<Policy, expanding_byte_allocator>
{
private:
	shared_byte_allocator _head_alloc;
	shared_byte_allocator _tail_alloc;
	function<shared_byte_allocator(void)> _constructor;

	tribool _has_allocated(
		shared_byte_allocator& alloc,
		const byte* p,
		std::size_t n
	) noexcept
	{
		return alloc?
			alloc.has_allocated(p, n):
			tribool{false};
	}

	std::size_t _max_size(
		shared_byte_allocator& alloc,
		std::size_t a
	) noexcept
	{
		return alloc?alloc.max_size(a):0;
	}

	shared_byte_allocator& _head(void)
	{
		if(!_head_alloc)
		{
			_head_alloc = _constructor();
		}
		return _head_alloc;
	}
public:
	expanding_byte_allocator(
		const function<shared_byte_allocator(void)>& constructor
	): _constructor(constructor)
	{ }

	typedef byte value_type;
	typedef std::size_t size_type;

	bool equal(byte_allocator* a) const
	noexcept override
	{
		expanding_byte_allocator* pa =
			dynamic_cast<expanding_byte_allocator*>(a);

		if(a != nullptr)
		{
			return	(_head_alloc == pa->_head_alloc) &&
				(_tail_alloc == pa->_tail_alloc);
		}
		return false;
	}

	size_type max_size(std::size_t a)
	noexcept override
	{
		size_type mhead = _max_size(_head(), a);
		size_type mtail = _max_size(_tail_alloc, a);

		return (mtail>mhead)?mtail:mhead;
	}

	tribool has_allocated(const byte* p, std::size_t n)
	noexcept override
	{
		return	_has_allocated(_head_alloc, p, n) ||
			_has_allocated(_tail_alloc, p, n);
	}

	byte* do_allocate(size_type n, size_type a)
	{
		if(n <= _head().max_size(a))
		{
			if(byte* p = _head().allocate(n, a))
			{
				return p;
			}
		}

		bool new_tail = false;
		if(!_tail_alloc)
		{
			_tail_alloc = shared_byte_allocator(
				expanding_byte_allocator(_constructor)
			);
			new_tail = true;
		}

		if(!new_tail || (n <= _max_size(_tail_alloc, a)))
		{
			return _tail_alloc.allocate(n, a);
		}
		return nullptr;
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		try { return do_allocate(n, a); }
		catch(std::bad_alloc&) {  }
		return nullptr;
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
		if(_has_allocated(_head_alloc, p, n))
		{
			assert(_head_alloc);
			_head_alloc.deallocate(p, n, a);
		}
		else if(!!_has_allocated(_tail_alloc, p, n))
		{
			assert(_tail_alloc);
			_tail_alloc.deallocate(p, n, a);
		}
		else
		{
			assert(!"Pointer not allocated by this allocator!");
		}
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

