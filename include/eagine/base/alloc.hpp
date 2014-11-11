/**
 *  @file eagine/base/alloc.hpp
 *  @brief Generic memory allocators.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ALLOC_1308281038_HPP
#define EAGINE_BASE_ALLOC_1308281038_HPP

#include <eagine/base/type.hpp>
#include <eagine/base/tribool.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/nil_t.hpp>
#include <utility>
#include <memory>
#include <limits>
#include <cassert>
#include <cstdlib>

namespace EAGine {
namespace base {

// byte_allocator
struct byte_allocator
{
	typedef byte value_type;
	typedef std::size_t size_type;

	virtual ~byte_allocator(void)
	noexcept
	{ }

	virtual
	byte_allocator* duplicate(void)
	noexcept = 0;

	virtual
	bool release(void)
	noexcept = 0;

	virtual
	bool equal(byte_allocator* a) const
	noexcept = 0;

	virtual
	size_type max_size(size_type a)
	noexcept = 0;

	virtual
	tribool has_allocated(const byte* p, size_type n)
	noexcept = 0;

	virtual
	byte* allocate(size_type n, size_type a)
	noexcept = 0;

	virtual
	void deallocate(byte* p, size_type n, size_type a)
	noexcept = 0;

	virtual
	bool can_reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept = 0;

	virtual
	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept = 0;

	virtual
	void eject_self(void)
	noexcept = 0;
};

// byte_alloc_managed_policy
struct byte_alloc_managed_policy
{
	inline
	byte_allocator* duplicate(byte_allocator* that)
	noexcept
	{
		return that;
	}

	inline
	bool release(byte_allocator*)
	noexcept
	{
		return false;
	}
};

// byte_alloc_ref_count_policy
class byte_alloc_ref_count_policy
{
private:
	std::size_t _ref_count;
public:
	byte_alloc_ref_count_policy(const byte_alloc_ref_count_policy&) =delete;

	byte_alloc_ref_count_policy&
	operator = (const byte_alloc_ref_count_policy&) = delete;

	byte_alloc_ref_count_policy&
	operator = (byte_alloc_ref_count_policy&& tmp) = delete;

	byte_alloc_ref_count_policy(void)
	 : _ref_count(1)
	{ }

	byte_alloc_ref_count_policy(byte_alloc_ref_count_policy&& tmp)
	 : _ref_count(tmp._ref_count)
	{
		tmp._ref_count = 0;
	}

	~byte_alloc_ref_count_policy(void)
	{
		assert(_ref_count == 0);
	}

	byte_allocator* duplicate(byte_allocator* that)
	noexcept
	{
		++_ref_count;
		return that;
	}

	bool release(byte_allocator*)
	noexcept
	{
		return (--_ref_count == 0);
	}
};

// default_byte_allocator_policy
typedef byte_alloc_ref_count_policy default_byte_allocator_policy;

// byte_allocator_impl
template <typename Policy, template <class> class DerivedTpl>
class byte_allocator_impl
 : public byte_allocator
{
private:
	Policy _policy;

	typedef DerivedTpl<Policy> Derived;

	Derived& derived(void)
	{
		return *static_cast<Derived*>(this);
	}
public:
	typedef std::size_t size_type;

	byte_allocator_impl(void) = default;
	byte_allocator_impl(byte_allocator_impl&&) = default;
	byte_allocator_impl(const byte_allocator_impl&) = delete;

	byte_allocator* duplicate(void)
	noexcept override
	{
		return _policy.duplicate(this);
	}

	bool release(void)
	noexcept override
	{
		return _policy.release(this);
	}

	bool can_reallocate(byte*, size_type, size_type, size_type)
	noexcept override
	{
		// TODO default impl
		return false;
	}

	byte* reallocate(byte*, size_type, size_type, size_type)
	noexcept override
	{
		// TODO default impl
		return nullptr;
	}

	template <typename Final>
	static Final* accomodate_derived(Final& that)
	noexcept
	{
		void* p = that.allocate(sizeof(Final), alignof(Final));
		return new(p) Final(std::move(that));
	}

	template <typename Final>
	static void eject_derived(Final& that)
	noexcept
	{
		Final tmp = std::move(that);
		tmp.deallocate(
			(byte*)(void*)&that,
			sizeof(Final),
			alignof(Final)
		);
	}

	Derived* accomodate_self(void)
	noexcept
	{
		return accomodate_derived(derived());
	}

	void eject_self(void)
	noexcept override
	{
		eject_derived(derived());
	}
};

// shared_byte_allocator
class shared_byte_allocator;

// byte_allocator_reference
class byte_allocator_reference
{
private:
	byte_allocator* _pballoc;

	friend class shared_byte_allocator;
public:
	byte_allocator_reference(byte_allocator& alloc)
	noexcept
	 : _pballoc(&alloc)
	{ }
};

// concrete_byte_allocator
template <template <class, class...> class ByteAllocTpl, typename ... Arg>
class concrete_byte_allocator
{
private:
	typedef ByteAllocTpl<byte_alloc_managed_policy, Arg...> ByteAlloc;

	ByteAlloc _alloc;
public:
	template <typename ... P>
	concrete_byte_allocator(P&& ... p)
	noexcept
	 : _alloc(std::forward<P>(p)...)
	{ }

	ByteAlloc& get(void)
	noexcept
	{
		return _alloc;
	}

	byte_allocator_reference reference(void)
	noexcept
	{
		return byte_allocator_reference(_alloc);
	}

	operator byte_allocator_reference (void)
	noexcept
	{
		return reference();
	}
};

// shared_byte_allocator
class shared_byte_allocator
{
private:
	byte_allocator* _pballoc;

	template <typename X>
	static byte_allocator* _get_new(
		X&& that,
		typename meta::enable_if<
			meta::is_convertible<X*, byte_allocator*>::value
		>::type* = nullptr
	) noexcept
	{
		try { return that.accomodate_self(); }
		catch(std::bad_alloc&) { }
		return nullptr;
	}

	void _cleanup(void)
	noexcept
	{
		if(_pballoc)
		{
			if(_pballoc->release())
			{
				_pballoc->eject_self();
			}
		}
	}

	byte_allocator* _release(void)
	noexcept
	{
		byte_allocator* result = _pballoc;
		_pballoc = nullptr;
		return result;
	}

	byte_allocator* _copy(void) const
	noexcept
	{
		return _pballoc?_pballoc->duplicate():nullptr;
	}
public:
	typedef byte value_type;
	typedef std::size_t size_type;

	shared_byte_allocator(const shared_byte_allocator& that)
	noexcept
	 : _pballoc(that._copy())
	{ }

	shared_byte_allocator(shared_byte_allocator&& tmp)
	noexcept
	 : _pballoc(tmp._release())
	{ }

	shared_byte_allocator(byte_allocator_reference mballoc)
	noexcept
	 : _pballoc(mballoc._pballoc)
	{ }

	template <
		typename X,
		typename = typename meta::enable_if<
			meta::is_base_of<byte_allocator, X>::value
		>::type
	>
	shared_byte_allocator(X&& x)
	noexcept
	 : _pballoc(_get_new(std::forward<X>(x)))
	{ }

	shared_byte_allocator& operator = (const shared_byte_allocator& that)
	noexcept
	{
		_cleanup();
		_pballoc = that._copy();
		return *this;
	}

	shared_byte_allocator& operator = (shared_byte_allocator&& that)
	noexcept
	{
		_cleanup();
		_pballoc = that._release();
		return *this;
	}

	~shared_byte_allocator(void)
	noexcept
	{
		_cleanup();
	}

	size_type max_size(size_type a) const
	noexcept
	{
		return _pballoc?_pballoc->max_size(a):0;
	}

	tribool has_allocated(const byte* p, size_type n)
	noexcept
	{
		return _pballoc?_pballoc->has_allocated(p, n):tribool{false};
	}

	byte* allocate(size_type n, size_type a)
	noexcept
	{
		return _pballoc?_pballoc->allocate(n, a):nullptr;
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept
	{
		if(_pballoc)
		{
			_pballoc->deallocate(p, n, a);
		}
		else
		{
			assert(p == nullptr);
		}
	}

	bool can_reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept
	{
		return _pballoc?_pballoc->can_reallocate(p, o, n, a):false;
	}

	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept
	{
		return _pballoc?_pballoc->reallocate(p, o, n, a):nullptr;
	}

	friend bool operator == (
		const shared_byte_allocator& a,
		const shared_byte_allocator& b
	)
	noexcept
	{
		if((a._pballoc == nullptr) && (b._pballoc == nullptr))
		{
			return true;
		}
		else if(a._pballoc)
		{
			return a._pballoc->equal(b._pballoc);
		}
		return false;
	}

	friend bool operator != (
		const shared_byte_allocator& a,
		const shared_byte_allocator& b
	)
	noexcept
	{
		return !(a == b);
	}

	template <typename ByteAlloc>
	ByteAlloc& as(void)
	{
		ByteAlloc* pa = dynamic_cast<ByteAlloc*>(_pballoc);
		if(pa == nullptr)
		{
			throw std::bad_cast();
		}
		return *pa;
	}
};

// c_byte_reallocator
template <typename Policy = default_byte_allocator_policy>
class c_byte_reallocator
 : public byte_allocator_impl<Policy, c_byte_reallocator>
{
public:
	typedef std::size_t size_type;

	bool equal(byte_allocator* a) const
	noexcept override
	{
		return dynamic_cast<c_byte_reallocator*>(a) != nullptr;
	}

	size_type max_size(size_type a)
	noexcept override
	{
		return std::numeric_limits<size_type>::max();
	}

	tribool has_allocated(const byte* p, size_type n)
	noexcept override
	{
		return indeterminate;
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		assert(a > 0);

		if(n == 0)
		{
			return nullptr;
		}

		byte* p = (byte*)std::malloc(n);

		// TODO fix if misaligned ?
		assert((reinterpret_cast<std::uintptr_t>(p) % a) == 0);

		return p;
	}

	void deallocate(byte* p, size_type, size_type)
	noexcept override
	{
		if(p != nullptr)
		{
			std::free(p);
		}
	}

	bool can_reallocate(byte*, size_type, size_type, size_type)
	noexcept override
	{
		return true;
	}

	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept override
	{
		assert(a > 0);

		if(n == 0)
		{
			deallocate(p, o, a);
			return nullptr;
		}

		p = (byte*)std::realloc(p, n);

		// TODO fix if misaligned ?
		assert((reinterpret_cast<std::uintptr_t>(p) % a) == 0);

		return p;
	}
};

// default byte_allocator
inline
byte_allocator_reference default_byte_allocator(void)
{
	static c_byte_reallocator<byte_alloc_managed_policy> balloc;
	return byte_allocator_reference(balloc);
}

// allocator - fwd
template <typename T>
class allocator;

template <>
class allocator<void>
{
private:
	shared_byte_allocator _sba; 
public:
	const shared_byte_allocator& _get_sba(void) const { return _sba; }

	typedef meta::nil_t value_type;
	typedef void* pointer;
	typedef const void* const_pointer;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template <typename U>
	struct rebind
	{
		typedef allocator<U> other;
	};

	template <typename U>
	allocator(const allocator<U>& that)
	 : _sba(that._get_sba())
	{ }

	allocator(shared_byte_allocator&& sba)
	noexcept
	 : _sba(std::move(sba))
	{ }

	allocator(void)
	noexcept
	 : _sba(default_byte_allocator())
	{ }

	template <typename ByteAlloc>
	ByteAlloc& as(void)
	{
		return _sba.as<ByteAlloc>();
	}
};


// allocator
template <typename T>
class allocator
{
private:
	shared_byte_allocator _sba; 
public:
	const shared_byte_allocator& _get_sba(void) const { return _sba; }

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
		typedef allocator<U> other;
	};

	template <typename U>
	allocator(const allocator<U>& that)
	 : _sba(that._get_sba())
	{ }

	allocator(shared_byte_allocator&& sba)
	noexcept
	 : _sba(std::move(sba))
	{ }

	allocator(void)
	noexcept
	 : _sba(default_byte_allocator())
	{ }

	template <typename ByteAlloc>
	ByteAlloc& as(void)
	{
		return _sba.as<ByteAlloc>();
	}

	T* address(T& r)
	noexcept
	{
		return std::allocator<T>().address(r);
	}

	const T* address(const T& r)
	noexcept
	{
		return std::allocator<T>().address(r);
	}

	size_type max_size(void) const
	noexcept
	{
		return _sba.max_size(alignof(T));
	}

	T* allocate(size_type n, const void* = nullptr)
	{
		byte* p = _sba.allocate(n*sizeof(T), alignof(T));

		assert((reinterpret_cast<std::uintptr_t>(p) % alignof(T)) == 0);

		if(p == nullptr)
		{
			throw std::bad_alloc();
		}

		return reinterpret_cast<T*>(p);
	}

	void deallocate(T* p, size_type n)
	{
		_sba.deallocate(
			reinterpret_cast<byte*>(p),
			n*sizeof(T),
			alignof(T)
		);
	}

	friend bool operator == (const allocator& a, const allocator& b)
	noexcept
	{
		return(a._sba == b._sba);
	}

	friend bool operator != (const allocator& a, const allocator& b)
	noexcept
	{
		return(a._sba != b._sba);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

