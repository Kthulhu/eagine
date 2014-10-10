/**
 *  @file eagine/dbg/alloc.hpp
 *  @brief Allocator decorator printing info about called functions
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DBG_ALLOC_1308281038_HPP
#define EAGINE_DBG_ALLOC_1308281038_HPP

#include <eagine/base/type_name.hpp>
#include <iostream>
#include <memory>

namespace EAGine {
namespace dbg {

template <typename A, typename VT>
class verbose_alloc_dec_tpl;

template <typename A>
class verbose_alloc_dec_tpl<A, void>
{
private:
	std::ostream& _out;
	A _a;
public:
	template <typename U>
	struct rebind
	{
		typedef verbose_alloc_dec_tpl<
			typename std::allocator_traits<A>
				::template rebind_alloc<U>,
			U
		> other;
	};

	verbose_alloc_dec_tpl(void)
	 : _out(std::cerr)
	 , _a()
	{ }

	verbose_alloc_dec_tpl(const verbose_alloc_dec_tpl&)
		= default;

	verbose_alloc_dec_tpl(const A& a)
	 : _out(std::cerr)
	 , _a(a)
	{ }

	template <typename ... Arg>
	verbose_alloc_dec_tpl(Arg&&...arg)
	 : _out(std::cerr)
	 , _a(std::forward<Arg>(arg)...)
	{ }
};

template <typename A, typename VT>
class verbose_alloc_dec_tpl
{
private:
	std::ostream& _out;
	A _a;

	static inline auto _alloc_type_name(void)
	{
		return base::type_name<A>();
	}

	template <typename X>
	static typename X::reference _r_hlp(X*);
	static void _r_hlp(...);

	template <typename X>
	static typename X::const_reference _cr_hlp(X*);
	static void _cr_hlp(...);
public:
	typedef typename std::allocator_traits<A>::value_type
		value_type;
	typedef typename std::allocator_traits<A>::pointer
		pointer;
	typedef typename std::allocator_traits<A>::const_pointer
		const_pointer;

	typedef decltype(_r_hlp((A*)0)) reference;
	typedef decltype(_cr_hlp((A*)0)) const_reference;

	typedef typename std::allocator_traits<A>::size_type
		size_type;
	typedef typename std::allocator_traits<A>::difference_type
		difference_type;

	template <typename U>
	struct rebind
	{
		typedef verbose_alloc_dec_tpl<
			typename std::allocator_traits<A>
				::template rebind_alloc<U>,
			U
		> other;
	};

	verbose_alloc_dec_tpl(void)
	 : _out(std::cerr)
	 , _a()
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::default construction"
			<< std::endl;
	}

	verbose_alloc_dec_tpl(const verbose_alloc_dec_tpl&)
		= default;

	verbose_alloc_dec_tpl(const A& a)
	 : _out(std::cerr)
	 , _a(a)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::copy construction"
			<< std::endl;
	}

	template <typename ... Arg>
	verbose_alloc_dec_tpl(Arg&& ... arg)
	 : _out(std::cerr)
	 , _a(std::forward<Arg>(arg)...)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::init construction"
			<< std::endl;
	}

	pointer address(reference v) const
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::address(v) = "
			<< std::flush;
		pointer r = _a.address(v);
		_out	<< r
			<< std::endl;
		return r;
	}

	const_pointer address(const_reference v) const
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::address(v) const = "
			<< std::flush;
		const_pointer r = _a.address(v);
		_out	<< r
			<< std::endl;
		return r;
	}

	pointer allocate(size_type n)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::allocate("
			<< n
			<< ") = "
			<< std::flush;
		pointer r = _a.allocate(n);
		_out	<< r
			<< std::endl;
		return r;
	}

	pointer allocate(size_type n, const void* hint)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::allocate("
			<< n
			<< ", "
			<< hint
			<< ") = "
			<< std::flush;
		pointer r = _a.allocate(n, hint);
		_out	<< r
			<< std::endl;
		return r;
	}

	void deallocate(pointer p, size_type n)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::deallocate("
			<< p
			<< ", "
			<< n
			<< ") = "
			<< std::flush;
		_a.deallocate(p, n);
		_out	<< "done"
			<< std::endl;
	}

	void construct(pointer p, const_reference v)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::construct("
			<< p
			<< ", v) = "
			<< std::flush;
		_a.construct(p, v);
		_out	<< "done"
			<< std::endl;
	}

	template <typename U, typename ... Arg>
	void construct(U* p, Arg&& ... arg)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::construct("
			<< p
			<< ", arg...) = "
			<< std::flush;
		_a.construct(p, std::forward<Arg>(arg)...);
		_out	<< "done"
			<< std::endl;
	}

	void destroy(pointer p)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::destroy("
			<< p
			<< ") = "
			<< std::flush;
		_a.destroy(p);
		_out	<< "done"
			<< std::endl;
	}

	template <typename U>
	void destroy(U* p)
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::destroy<U>("
			<< p
			<< ") = "
			<< std::flush;
		_a.destroy(p);
		_out	<< "done"
			<< std::endl;
	}

	size_type max_size(void) const
	{
		_out	<< "|"
			<< _alloc_type_name()
			<< "::max_size() = "
			<< std::flush;
		size_type r = _a.max_size();
		_out	<< r
			<< std::endl;
		return r;
	}

	friend bool operator == (
		const verbose_alloc_dec_tpl& a,
		const verbose_alloc_dec_tpl& b
	)
	{
		a._out	<< "|"
			<< _alloc_type_name()
			<< "::operator==() = "
			<< std::flush;
		bool r = (a._a == b._b);
		a._out	<< r
			<< std::endl;
		return r;
	}

	friend bool operator != (
		const verbose_alloc_dec_tpl& a,
		const verbose_alloc_dec_tpl& b
	)
	{
		a._out	<< "|"
			<< _alloc_type_name()
			<< "::operator!=() = "
			<< std::flush;
		bool r = (a._a != b._b);
		a._out	<< r
			<< std::endl;
		return r;
	}
};

template <typename A>
using verbose_allocator_decorator =
	verbose_alloc_dec_tpl<A, typename A::value_type>;


} // namespace dbg
} // namespace EAGine

#endif //include guard

