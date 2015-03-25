/**
 *  @file eagine/base/memory_block.hpp
 *  @brief Memory block.
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_MEMORY_BLOCK_1408161723_HPP
#define EAGINE_BASE_MEMORY_BLOCK_1408161723_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/base/type.hpp>
#include <cstdint>
#include <cstddef>
#include <cassert>

namespace eagine {
namespace base {

template <typename Derived, typename Slice, typename T, typename E>
class crtp_base_memory_range
{
protected:
	inline
	Derived& self(void)
	noexcept
	{
		return *static_cast<Derived*>(this);
	}

	inline
	const Derived& self(void) const
	noexcept
	{
		return *static_cast<const Derived*>(this);
	}
public:
	explicit
	operator bool (void) const
	noexcept
	{
		return	(self().addr() != nullptr) &&
			(self().size() != 0);
	}

	bool empty(void) const
	noexcept
	{
		return self().size() == 0;
	}

	typedef T value_type;
	typedef E element_type;

	typedef typename meta::add_lvalue_reference<
		typename meta::add_const<element_type>::type
	>::type const_reference;

	typedef typename meta::add_lvalue_reference<
		element_type
	>::type reference;

	typedef typename meta::add_pointer<
		typename meta::add_const<element_type>::type
	>::type const_pointer;

	typedef typename meta::add_pointer<
		element_type
	>::type pointer;

	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef const_pointer const_iterator;
	typedef pointer iterator;

	const_iterator begin(void) const
	noexcept
	{
		return static_cast<const_iterator>(self().addr());
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<!Const, iterator>::type
	begin(void)
	noexcept
	{
		return static_cast<iterator>(self().addr());
	}

	const_iterator offs(size_type n) const
	noexcept
	{
		assert((n == 0) || (self().addr()));
		assert(n <= self().size());
		return static_cast<const_iterator>(self().addr())+n;
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<!Const, iterator>::type
	offs(size_type n)
	noexcept
	{
		assert((n == 0) || (self().addr()));
		assert(n <= self().size());
		return static_cast<iterator>(self().addr())+n;
	}

	const_iterator end(void) const
	noexcept
	{
		return offs(self().size());
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<!Const, iterator>::type
	end(void)
	noexcept
	{
		return offs(self().size());
	}

	const_reference operator [](size_type n) const
	{
		assert(!empty());
		return *offs(n);
	}

	reference operator [](size_type n)
	{
		assert(!empty());
		return *offs(n);
	}

	Slice slice(size_type o, size_type s) const
	noexcept
	{
		assert(o+s <= self().size());
		return Slice(offs(o), s);
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<!Const, Slice>::type
	slice(size_type o, size_type s)
	noexcept
	{
		assert(o+s <= self().size());
		return Slice(offs(o), s);
	}

	Slice slice(size_type o) const
	noexcept
	{
		assert(o <= self().size());
		return slice(o, self().size()-o);
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<!Const, Slice>::type
	slice(size_type o)
	noexcept
	{
		assert(o <= self().size());
		return slice(o, self().size()-o);
	}

	friend bool operator == (
		const crtp_base_memory_range& a,
		const crtp_base_memory_range& b
	) noexcept
	{
		return	(a.self().addr() == b.self().addr()) &&
			(a.self().size() == b.self().size());
	}

	friend bool operator != (
		const crtp_base_memory_range& a,
		const crtp_base_memory_range& b
	) noexcept
	{
		return	(a.self().addr() != b.self().addr()) ||
			(a.self().size() != b.self().size());
	}

	friend bool operator <  (
		const crtp_base_memory_range& a,
		const crtp_base_memory_range& b
	) noexcept
	{
		return	(a.self().addr() <  b.self().addr()) || (
			(a.self().addr() == b.self().addr()) &&
			(a.self().size() <  b.self().size())
		);
	}
};

template <bool Const>
class basic_memory_block
 : public crtp_base_memory_range<
	basic_memory_block<Const>,
	basic_memory_block<Const>,
	typename meta::conditional<Const, const void, void>::type,
	typename meta::conditional<Const, const byte, byte >::type
>
{
private:
	typedef typename meta::conditional<Const, const void, void >::type T; 
	typedef typename meta::conditional<Const, const byte, byte >::type B; 

	typedef crtp_base_memory_range<
		basic_memory_block<Const>,
		basic_memory_block<Const>,
		T, B
	> _base;

	T* _addr;
	std::size_t _size;

	static inline
	std::size_t _dist(B* b, B* e)
	noexcept
	{
		assert(b <= e);
		return std::size_t(e-b);
	}

	static
	std::uintptr_t _misalign(B* p, std::uintptr_t alignment)
	noexcept
	{
		return (std::uintptr_t(p) % alignment);
	}

	static
	std::uintptr_t _misalign(T* p, std::uintptr_t alignment)
	noexcept
	{
		return _misalign(static_cast<B*>(p), alignment);
	}
public:
	typedef typename _base::const_iterator const_iterator;

	using _base::begin;
	using _base::offs;
	using _base::end;

	basic_memory_block(void)
	noexcept
	 : _addr(nullptr)
	 , _size(0)
	{ }

	basic_memory_block(T* bgn_, T* end_)
	noexcept
	 : _addr(bgn_)
	 , _size(_dist(static_cast<B*>(bgn_),static_cast<B*>(end_)))
	{ }

	basic_memory_block(T* addr_, std::size_t size_)
	noexcept
	 : _addr(addr_)
	 , _size(size_)
	{ }

	basic_memory_block(
		const basic_memory_block<false>& that
	) noexcept
	 : _addr(that.addr())
	 , _size(that.size())
	{ }

	T* addr(void) const
	noexcept
	{
		return _addr;
	}

	std::size_t size(void) const
	noexcept
	{
		return _size;
	}

	const_iterator aligned_begin(std::uintptr_t alignment) const
	noexcept
	{
		std::uintptr_t ma = _misalign(begin(), alignment);
		return static_cast<const_iterator>(
			(begin())+
			(ma?alignment-ma:0)
		);
	}

	const_iterator aligned_end(std::uintptr_t alignment) const
	noexcept
	{
		return static_cast<const_iterator>(
			(end())-
			_misalign(end(), alignment)
		);
	}

	basic_memory_block slice_to_align(std::size_t alignment) const
	noexcept
	{
		B* b = aligned_begin(alignment);
		B* e = aligned_end(alignment);

		assert((std::uintptr_t(b) % alignment) == 0);
		assert((std::uintptr_t(e) % alignment) == 0);

		if(e < b) e = b;

		return basic_memory_block(b, e);
	}
};

typedef basic_memory_block<false> memory_block;
typedef basic_memory_block<true > const_memory_block;

template <typename Derived, typename Slice, typename T, typename E>
class crtp_memory_range
 : public crtp_base_memory_range<Derived, Slice, T, E>
{
public:
	basic_memory_block<true> block(void) const
	noexcept
	{
		return {
			this->self().addr(),
			this->self().size()*
			sizeof(E)
		};
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<
		!Const,
		basic_memory_block<false>
	>::type block(void)
	noexcept
	{
		return {
			this->self().addr(),
			this->self().size()*
			sizeof(E)
		};
	}

	operator basic_memory_block<true>(void) const
	noexcept
	{
		return block();
	}

	template <
		bool Const = meta::is_const<T>::value,
		typename = typename meta::enable_if<!Const>::type
	>
	operator basic_memory_block<false>(void)
	noexcept
	{
		return block();
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

