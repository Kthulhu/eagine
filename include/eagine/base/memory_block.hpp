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
class basic_memory_block
{
private:
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
		const basic_memory_block<
			typename meta::remove_const<T>::type
		>& that
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
};

typedef basic_memory_block<void> memory_block;
typedef basic_memory_block<const void> const_memory_block;

template <typename T>
class typed_memory_block
 : public basic_memory_block<T>
{
public:
	using basic_memory_block<T>::basic_memory_block;

	typed_memory_block(
		const basic_memory_block<
			typename meta::add_same_constness<T, void>::type
		>& raw_block
	): basic_memory_block<T>(
		static_cast<T*>(raw_block.address()),
		raw_block.size() / sizeof(T)
	) { }

	T& at(std::size_t pos) const
	{
		assert(pos < this->size());
		return *(this->address()+pos);
	}
};

typedef typed_memory_block<byte> byte_block;
typedef typed_memory_block<const byte> const_byte_block;

} // namespace base
} // namespace EAGine

#endif //include guard

