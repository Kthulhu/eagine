/**
 *  @file eagine/base/varray.hpp
 *  @brief Array of POD elements with variable size specified at construction.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_VARRAY_1308281038_HPP
#define EAGINE_BASE_VARRAY_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/meta/type_traits.hpp>
#include <cassert>

namespace EAGine {
namespace base {

// basic_pod_varray
template <typename T, typename S>
struct basic_pod_varray
{
//private:
	static_assert(
		meta::is_pod<T>::value,
		"varray elements must be POD"
	);

	S _size;
	T _data[1];

	typedef typename meta::conditional<
			alignof(T) >= alignof(S),
			T, S
	>::type _alloc_unit_t;

	static S _alloc_unit_c(S n)
	noexcept
	{
		if(alignof(T)>=alignof(decltype(_size)))
		{
			return n+(sizeof(S)/sizeof(T))+
				((sizeof(S)%sizeof(T))?1:0);
		}
		else
		{
			return 1+((n*sizeof(T))/sizeof(S))+
				(((n*sizeof(T))%sizeof(S))?1:0);
		}
	}

	S _alloc_unit_c(void) const
	noexcept
	{
		return _alloc_unit_c(_size);
	}
//public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* iterator;
	typedef typename meta::add_const<T>::type* const_iterator;

	std::size_t instance_size(void) const
	noexcept
	{
		return sizeof(_alloc_unit_t)*_alloc_unit_c();
	}

	S size(void) const
	noexcept
	{
		return _size;
	}

	bool empty(void) const
	noexcept
	{
		return size() == S(0);
	}

	iterator begin(void)
	noexcept
	{
		return _data;
	}

	const_iterator begin(void) const
	noexcept
	{
		return _data;
	}

	iterator end(void)
	noexcept
	{
		return _data+_size;
	}

	const_iterator end(void) const
	noexcept
	{
		return _data+_size;
	}

	reference at(S pos)
	noexcept
	{
		assert(pos < _size);
		return _data[pos];
	}

	const_reference at(S pos) const
	noexcept
	{
		assert(pos < _size);
		return _data[pos];
	}

	reference operator [](S pos)
	noexcept
	{
		return at(pos);
	}

	const_reference operator [](S pos) const
	noexcept
	{
		return at(pos);
	}
};

// free_pod_varray
template <typename T, typename S, typename Allocator>
static inline
typename meta::enable_if<
	meta::is_same<
		typename meta::conditional<
			alignof(T) >= alignof(S),
			T, S
		>::type,
		typename Allocator::value_type
	>::value
>::type
free_basic_pod_varray(basic_pod_varray<T,S>* ptr, Allocator& alloc)
{
	if(ptr != nullptr)
	{
		typedef typename meta::conditional<
			alignof(T) >= alignof(S),
			T, S
		>::type E;
		alloc.deallocate(
			(E*)(void*)ptr,
			ptr->_alloc_unit_c()
		);
	}
}

// free_basic_pod_varray
template <typename T, typename S>
static inline
void free_basic_pod_varray(basic_pod_varray<T,S>* ptr)
{
	allocator<typename basic_pod_varray<T,S>::_alloc_unit_t> alloc;
	free_basic_pod_varray<T,S>(ptr, alloc);
}

// make_basic_pod_varray
template <typename T, typename S, typename Allocator>
static inline
typename meta::enable_if<
	meta::is_same<
		typename meta::conditional<
			alignof(T)>=alignof(S),
			T, S
		>::type,
		typename Allocator::value_type
	>::value,
	basic_pod_varray<T,S>*
>::type
make_basic_pod_varray(S n, Allocator& alloc)
{
	void* ptr = alloc.allocate(basic_pod_varray<T,S>::_alloc_unit_c(n));

	if(ptr != nullptr)
	{
		*static_cast<S*>(ptr) = n;
	}

	return static_cast<basic_pod_varray<T,S>*>(ptr);
}

// make_basic_pod_varray
template <typename T, typename S>
static inline
basic_pod_varray<T,S>*
make_basic_pod_varray(S n)
{
	allocator<typename basic_pod_varray<T,S>::_alloc_unit_t> alloc;
	return make_basic_pod_varray(n, alloc);
}

// make_basic_pod_varray
template <typename T, typename S, typename Allocator>
static inline
basic_pod_varray<T,S>*
make_basic_pod_varray(S n, T v, Allocator& alloc)
{
	basic_pod_varray<T,S>* ptr =
		make_basic_pod_varray<T,S>(n, alloc);

	if(ptr != nullptr)
	{
		assert(ptr->_size == n);
		std::fill(ptr->begin(), ptr->end(), v);
	}

	return ptr;
}

// make_basic_pod_varray
template <typename T, typename S>
static inline
basic_pod_varray<T,S>*
make_basic_pod_varray(S n, T v)
{
	allocator<typename basic_pod_varray<T,S>::_alloc_unit_t> alloc;
	return make_basic_pod_varray<T,S>(n, v, alloc);
}

// make_basic_pod_varray
template <typename T, typename S, typename Allocator, typename Iterator>
static inline
basic_pod_varray<T,S>*
make_basic_pod_varray(Iterator i, Iterator e, Allocator& alloc)
{
	using std::distance;

	assert(distance(i, e) >= 0);
	const S n = S(distance(i, e));

	basic_pod_varray<T,S>* ptr =
		make_basic_pod_varray<T,S>(n, alloc);

	if(ptr != nullptr)
	{
		assert(ptr->_size == n);
		std::copy(i, e, ptr->begin());
	}

	return ptr;
}

// make_basic_pod_varray
template <typename T, typename S, typename Iterator>
static inline
basic_pod_varray<T,S>*
make_basic_pod_varray(Iterator i, Iterator e)
{
	allocator<typename basic_pod_varray<T,S>::_alloc_unit_t> alloc;
	return make_basic_pod_varray<T,S>(i, e, alloc);
}

// make_basic_pod_varray
template <typename T, typename S, typename Allocator>
static inline 
basic_pod_varray<T,S>*
make_basic_pod_varray(const std::initializer_list<T>& il, Allocator& alloc)
{
	return make_basic_pod_varray<T,S>(il.begin(), il.end(), alloc);
}

// make_basic_pod_varray
template <typename T, typename S>
static inline 
basic_pod_varray<T,S>*
make_basic_pod_varray(const std::initializer_list<T>& il)
{
	allocator<typename basic_pod_varray<T,S>::_alloc_unit_t> alloc;
	return make_basic_pod_varray<T,S>(il.begin(), il.end(), alloc);
}

} // namespace base
} // namespace EAGine

#endif //include guard

