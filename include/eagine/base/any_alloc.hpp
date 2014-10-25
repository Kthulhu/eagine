/**
 *  @file eagine/base/any_alloc.hpp
 *  @brief Type erasure for memory allocators.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ANY_ALLOC_1308281038_HPP
#define EAGINE_BASE_ANY_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <utility>

namespace EAGine {
namespace base {

template <typename T>
class any_allocator
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template <typename U>
	struct rebind
	{
		typedef any_allocator<U> other;
	};
private:
	struct _intf
	{
		virtual ~_intf(void) { }

		virtual size_type max(void) const noexcept = 0;

		virtual pointer alloc(size_type n) = 0;
		virtual void dealloc(pointer p, size_type n) = 0;

		virtual bool eq(const _intf&, const _intf&) noexcept = 0;
		virtual bool ne(const _intf&, const _intf&) noexcept = 0;
	};

	template <typename Alloc>
	struct _impl : _intf
	{
		Alloc _alloc;

		template <typename ... Arg>
		_impl(Arg&& ... arg)
		 : _alloc(std::forward<Arg>(arg)...)
		{ }

		size_type max(void) const noexcept
		{
			return _alloc.max_size();
		}

		pointer alloc(size_type n)
		{
			return _alloc.allocate(n);
		}

		void dealloc(pointer p, size_type n)
		{
			_alloc.deallocate(p, n);
		}

		bool eq(const _intf& a, const _intf& b) noexcept
		{
			const _impl* ia = dynamic_cast<const _impl*>(&a);
			const _impl* ib = dynamic_cast<const _impl*>(&b);

			if((!ia) || (!ib)) return false;
			return ia->_alloc == ib->_alloc;
		}

		bool ne(const _intf& a, const _intf& b) noexcept
		{
			const _impl* ia = dynamic_cast<const _impl*>(&a);
			const _impl* ib = dynamic_cast<const _impl*>(&b);

			if((!ia) || (!ib)) return false;
			return ia->_alloc != ib->_alloc;
		}
	};

	shared_ptr<_intf> _pimpl;
public:
	any_allocator(void) = default;
	any_allocator(const any_allocator&) = default;
	any_allocator(any_allocator&&) = default;

	template <typename Alloc>
	any_allocator(const Alloc& alloc)
	 : _pimpl(allocate_shared<_impl<Alloc>>(
		typename Alloc::
			template rebind<_impl<Alloc>>::
				other(alloc),
		alloc
	))
	{ }

	size_type max_size(void) const
	noexcept
	{
		assert(_pimpl);
		return _pimpl->max();
	}

	pointer allocate(size_type n)
	{
		assert(_pimpl);
		return _pimpl->alloc(n);
	}

	void deallocate(pointer p, size_type n)
	noexcept
	{
		assert(_pimpl);
		_pimpl->dealloc(p, n);
	}

	template <typename U, typename ... A>
	void construct(U* p, A&&...a)
	noexcept(noexcept(U(std::forward<A>(a)...)))
	{
		::new((void*)p) U(std::forward<A>(a)...);
	}

	void destroy(pointer p)
	noexcept(noexcept(((T*)p)->~T()))
	{
		((T*)p)->~T();
	}

	template <typename U>
	void destroy(U* p)
	noexcept(noexcept(p->~U()))
	{
		p->~U();
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

