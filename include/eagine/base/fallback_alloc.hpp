/**
 *  @file eagine/base/fallback_alloc.hpp
 *  @brief Allocator with fallback.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_FALLBACK_ALLOC_1308281038_HPP
#define EAGINE_BASE_FALLBACK_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>

namespace EAGine {
namespace base {

template <typename Policy = default_byte_allocator_policy>
class byte_allocator_with_fallback
 : public byte_allocator_impl<Policy, byte_allocator_with_fallback>
{
private:
	std::size_t _fbk_size;
	std::size_t _fbk_max;
	shared_byte_allocator _dft;
	shared_byte_allocator _fbk;
public:
	byte_allocator_with_fallback(byte_allocator_with_fallback&&) = default;

	byte_allocator_with_fallback(
		shared_byte_allocator&& dft,
		shared_byte_allocator&& fbk = default_byte_allocator()
	): _fbk_size(0)
	 , _fbk_max(0)
	 , _dft(std::move(dft))
	 , _fbk(std::move(fbk))
	{ }

	typedef byte value_type;
	typedef std::size_t size_type;

	bool equal(byte_allocator* a) const
	noexcept override
	{
		byte_allocator_with_fallback* pa =
			dynamic_cast<byte_allocator_with_fallback*>(a);

		if(a != nullptr)
		{
			return (_dft == pa->_dft) && (_fbk == pa->_fbk);
		}
		return false;
	}

	std::size_t required_fallback_size(void) const
	noexcept
	{
		return _fbk_max;
	}

	size_type max_size(std::size_t a)
	noexcept override
	{
		size_type mdft = _dft.max_size(a);
		size_type mfbk = _fbk.max_size(a);

		return (mfbk>mdft)?mfbk:mdft;
	}

	tribool has_allocated(const byte* p, std::size_t n)
	noexcept
	{
		return	_dft.has_allocated(p, n) ||
			_fbk.has_allocated(p, n);
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		if(n <= _dft.max_size(a))
		{
			if(byte* p = _dft.allocate(n, a))
			{
				return p;
			}
		}

		_fbk_size += n;
		if(_fbk_max < _fbk_size)
		{
			_fbk_max = _fbk_size;
		}
		return _fbk.allocate(n, a);
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
		if(_dft.has_allocated(p, n))
		{
			_dft.deallocate(p, n, a);
		}
		else if(!!_fbk.has_allocated(p, n))
		{
			_fbk_size -= n;
			_fbk.deallocate(p, n, a);
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

