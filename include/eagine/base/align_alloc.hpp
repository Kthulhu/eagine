/**
 *  @file eagine/base/align_alloc.hpp
 *  @brief Multi-alignment byte allocator
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ALIGN_ALLOC_1308281038_HPP
#define EAGINE_BASE_ALIGN_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/type_to_value.hpp>
#include <eagine/meta/int_const.hpp>
#include <eagine/meta/int_sequence.hpp>
#include <eagine/meta/instead_of.hpp>

namespace EAGine {
namespace base {

// multi_align_byte_allocator - fwd
template <typename AlignSeq, typename Policy = default_byte_allocator_policy>
class multi_align_byte_allocator;

// multi_align_byte_allocator
template <std::size_t ... Align, typename Policy>
class multi_align_byte_allocator<
	meta::integer_sequence<std::size_t, Align...>,
	Policy
>: public byte_allocator_impl<
	Policy,
	multi_align_byte_allocator,
	meta::integer_sequence<std::size_t, Align...>
>
{
private:
	type_to_value<
		std::size_t,
		meta::integral_constant<std::size_t, Align>...
	> _alignment;

	type_to_value<
		shared_byte_allocator,
		meta::integral_constant<std::size_t, Align>...
	> _aligned_alloc;

	shared_byte_allocator _fallback_alloc;

	shared_byte_allocator& _get_alloc(std::size_t align)
	{
		assert(_alignment.size() == _aligned_alloc.size());
		for(std::size_t i=0; i<_alignment.size(); ++i)
		{
			if(_alignment[i] == align)
			{
				return _aligned_alloc[i];
			}
		}
		return _fallback_alloc;
	}
public:
	multi_align_byte_allocator(
		typename meta::instead_of<
			meta::integral_constant<std::size_t, Align>,
			shared_byte_allocator
		>::type ... aligned_alloc,
		shared_byte_allocator fallback_alloc = default_byte_allocator()
	): _alignment(Align...)
	 , _aligned_alloc(std::move(aligned_alloc)...)
	 , _fallback_alloc(std::move(fallback_alloc))
	{ }

	typedef byte value_type;
	typedef std::size_t size_type;

	bool equal(byte_allocator* a) const
	noexcept override
	{
		if(auto* that = dynamic_cast<multi_align_byte_allocator*>(a))
		{
			for(std::size_t i=0; i<_aligned_alloc.size(); ++i)
			{
				if(_aligned_alloc[i] != that->_aligned_alloc[i])
				{
					return false;
				}
			}

			return _fallback_alloc == that->_fallback_alloc;
		}
		return false;
	}
	
	size_type max_size(std::size_t a)
	noexcept override
	{
		return _get_alloc(a).max_size(a);
	}

	tribool has_allocated(const byte* p, std::size_t n)
	noexcept override
	{
		for(std::size_t i=0; i<_aligned_alloc.size(); ++i)
		{
			if(_aligned_alloc[i].has_allocated(p, n))
			{
				return true;
			}
		}
		return _fallback_alloc.has_allocated(p, n);
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		return _get_alloc(a).allocate(n, a);
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
		assert(!!_get_alloc(a).has_allocated(p, n));
		_get_alloc(a).deallocate(p, n, a);
	}
};


} // namespace base
} // namespace EAGine

#endif //include guard

