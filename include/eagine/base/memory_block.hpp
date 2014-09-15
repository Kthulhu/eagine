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

	basic_memory_block(T* addr, std::size_t size)
	 : _addr(addr)
	 , _size(size)
	{ }

	basic_memory_block(
		const basic_memory_block<false>& that
	): _addr(that.address())
	 , _size(that.size())
	{ }

	explicit operator bool (void) const
	{
		return (_addr != nullptr) && (_size != 0);
	}

	T* address(void) const
	{
		return _addr;
	}

	std::size_t size(void) const
	{
		return _size;
	}

	basic_memory_block slice(std::size_t begin, std::size_t size) const
	{
		assert(begin+size <= _size);
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

template <typename T>
class typed_memory_range
{
private:
	T* _addr;
	std::size_t _size;

	T* _cast(typename meta::add_same_constness<T, void>::type* ptr)
	{
		assert((std::size_t)ptr % alignof(T) == 0);
		return static_cast<T*>(ptr);
	}
public:
	typedef basic_memory_block<meta::is_const<T>::value> raw_block;

	typed_memory_range(T* addr, std::size_t size)
	 : _addr(addr)
	 , _size(size)
	{ }

	typed_memory_range(const raw_block& raw)
	 : _addr(_cast(raw.address()))
	 , _size(raw.size() / sizeof(T))
	{ }

	raw_block block(void) const
	{
		return raw_block(_addr, _size*sizeof(T));
	}

	operator raw_block (void) const
	{
		return block();
	}

	typedef T* iterator;
	typedef T& reference;

	bool empty(void) const
	{
		return _size == 0;
	}

	std::size_t size(void) const
	{
		return _size;
	}

	T& at(std::size_t pos) const
	{
		assert(pos < this->_size);
		return *(this->_addr+pos);
	}

	T* begin(void) const
	{
		return this->_addr;
	}

	T* end(void) const
	{
		return this->_addr+this->_size;
	}

	typed_memory_range slice(std::size_t begin, std::size_t size) const
	{
		assert(begin+size <= _size);
		return typed_memory_range(_addr+begin, size);
	}

	typed_memory_range slice(std::size_t begin) const
	{
		return slice(begin, _size-begin);
	}
};

typedef typed_memory_range<byte> byte_range;
typedef typed_memory_range<const byte> const_byte_range;

} // namespace base
} // namespace EAGine

#endif //include guard

