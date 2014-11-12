/**
 *  @file eagine/base/logging_alloc.hpp
 *  @brief Type erasure for memory allocators.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_LOGGING_ALLOC_1308281038_HPP
#define EAGINE_BASE_LOGGING_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <iostream>

namespace EAGine {
namespace base {

template <typename Policy = default_byte_allocator_policy>
class logging_byte_allocator
 : public byte_allocator_impl<Policy, logging_byte_allocator>
{
private:
	shared_byte_allocator _alloc;
	std::ostream& _out;
	std::string _label;

	typedef logging_byte_allocator<Policy> Self;
	Self& _self(void)
	{
		return *this;
	}

	typedef byte_allocator_impl<
		Policy,
		EAGine::base::logging_byte_allocator
	> Impl;

	std::ostream& _log(const char* action) const
	{
		return _out
			<< "allocator '"
			<< _label
			<< "' "
			<< (void*)this
			<< ": "
			<< action;
	}
public:
	typedef std::size_t size_type;

	logging_byte_allocator(logging_byte_allocator&& tmp)
	 : Impl(static_cast<Impl&&>(tmp))
	 , _alloc(std::move(tmp._alloc))
	 , _out(tmp._out)
	 , _label(tmp._label)
	{
		tmp._label.append(" (moved out)");
	}

	logging_byte_allocator(
		shared_byte_allocator&& alloc,
		std::ostream& out = std::cerr,
		std::string&& label = "alloc"
	) noexcept
	 : _alloc(alloc)
	 , _out(out)
	 , _label(std::move(label))
	{
		_log("construction")
			<< std::endl;
	}

	~logging_byte_allocator(void)
	noexcept
	{
		_log("destruction")
			<< std::endl;
	}

	byte_allocator* duplicate(void)
	noexcept override
	{
		byte_allocator* result = Impl::duplicate();
		_log("duplicate")
			<< " as "
			<< (void*)result
			<< std::endl;
		return result;
	}

	bool release(void)
	noexcept override
	{
		bool result = Impl::release();
		_log("release")
			<< " = "
			<< (result?"true":"false")
			<< std::endl;
		return result;
	}

	bool equal(byte_allocator* a) const
	noexcept override
	{
		bool result = false;
		if(Self* that = dynamic_cast<Self*>(a))
		{
			result = this->_alloc == that->_alloc;
		}
		_log("equal")
			<< "("
			<< (void*)a
			<< ")"
			<< " = "
			<< (result?"true":"false")
			<< std::endl;
		return result;
	}

	size_type max_size(size_type a)
	noexcept override
	{
		size_type result = _alloc.max_size(a);
		_log("max_size")
			<< "("
			<< a
			<< ")"
			<< " = "
			<< result
			<< std::endl;
		return result;
	}

	tribool has_allocated(const byte* p, size_type n)
	noexcept override
	{
		tribool result = _alloc.has_allocated(p, n);
		_log("has_allocated")
			<< "("
			<< (void*)p
			<< ", "
			<< n
			<< ")"
			<< " = "
			<< (result?"true":!result?"false":"unknown")
			<< std::endl;
		return result;
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		byte* result = _alloc.allocate(n, a);
		_log("allocate")
			<< "("
			<< n
			<< ", "
			<< a
			<< ")"
			<< " = "
			<< (void*)result
			<< std::endl;
		return result;
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
		_alloc.deallocate(p, n, a);
		_log("deallocate")
			<< "("
			<< (void*)p
			<< ", "
			<< n
			<< ", "
			<< a
			<< ")"
			<< std::endl;
	}

	bool can_reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept override
	{
		bool result = _alloc.can_reallocate(p, o, n, a);
		_log("can_reallocate")
			<< "("
			<< (void*)p
			<< ", "
			<< o
			<< ", "
			<< n
			<< ", "
			<< a
			<< ")"
			<< " = "
			<< (result?"true":"false")
			<< std::endl;
		return result;
	}

	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept override
	{
		byte* result = _alloc.reallocate(p, o, n, a);
		_log("reallocate")
			<< "("
			<< (void*)p
			<< ", "
			<< o
			<< ", "
			<< n
			<< ", "
			<< a
			<< ")"
			<< " = "
			<< (void*)result
			<< std::endl;
		return result;
	}

	Self* accomodate_self(void)
	noexcept
	{
		Self* result = Impl::accomodate_derived(_self());
		_log("accomodate_self")
			<< " = "
			<< (void*)result
			<< std::endl;
		return result;
	}

	void eject_self(void)
	noexcept override
	{
		_log("eject_self")
			<< std::endl;
		return Impl::eject_derived(_self());
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

