/**
 *  @file eagine/base/string.hpp
 *  @brief UTF-8 encoded string and string references.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_STRING_1308281038_HPP
#define EAGINE_BASE_STRING_1308281038_HPP

#include <string>
#include <cstring>
#include <type_traits>

namespace EAGine {
namespace base {

using ::std::string;

template <typename Char>
class basic_string_ref
{
private:
	Char* _ptr;
	std::size_t _len;

	typedef const basic_string_ref& pcself;
public:
	typedef Char value_type;
	typedef typename ::std::add_const<value_type>::type const_value_type;
	typedef typename ::std::remove_const<value_type>::type nonconst_value_type;

	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	typedef value_type* pointer;
	typedef value_type& reference;
	typedef value_type* iterator;
	typedef const_value_type* const_iterator;

	typedef ::std::reverse_iterator<iterator> reverse_iterator;
	typedef ::std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef ::std::basic_string<nonconst_value_type> string_type;

	basic_string_ref(void)
	 : _ptr("")
	 , _len(0)
	{ }

	basic_string_ref(value_type* ptr)
	 : _ptr(ptr)
	 , _len(::std::strlen(ptr))
	{ }

	basic_string_ref(value_type* ptr, size_type len)
	 : _ptr(ptr)
	 , _len(len)
	{ }

	basic_string_ref(const basic_string_ref& that)
	 : _ptr(that._ptr)
	 , _len(that._len)
	{ }

	template <typename Char_>
	basic_string_ref(
		const ::std::basic_string<Char_>& s,
		typename std::enable_if<std::is_const<Char>::value>::type* = nullptr
	): _ptr(s.data())
	 , _len(s.size())
	{ }

	basic_string_ref& operator = (const basic_string_ref& that)
	{
		this->_ptr = that._ptr;
		this->_len = that._len;
		return *this;
	}

	friend bool operator == (pcself a, pcself b)
	{
		if(a._len != b._len) return false;
		int cmp = ::std::strncmp(a._ptr, b._ptr, a._len);
		return cmp == 0;
	}

	friend bool operator != (pcself a, pcself b)
	{
		if(a._len != b._len) return true;
		int cmp = ::std::strncmp(a._ptr, b._ptr, a._len);
		return cmp != 0;
	}

	friend bool operator <  (pcself a, pcself b)
	{
		return ::std::strcmp(a._ptr, b._ptr) <  0;
	}

	friend bool operator >  (pcself a, pcself b)
	{
		return ::std::strcmp(a._ptr, b._ptr) >  0;
	}

	friend bool operator <= (pcself a, pcself b)
	{
		return ::std::strcmp(a._ptr, b._ptr) <= 0;
	}

	friend bool operator >= (pcself a, pcself b)
	{
		return ::std::strcmp(a._ptr, b._ptr) >= 0;
	}

	size_type size(void) const
	{
		return _len;
	}

	size_type length(void) const
	{
		return _len;
	}

	const_value_type* c_str(void) const
	{
		return _ptr;
	}

	value_type* data(void)
	{
		return _ptr;
	}

	string_type str(void) const
	{
		return string_type(_ptr, _len);
	}
};

typedef basic_string_ref<char> string_ref;
typedef basic_string_ref<const char> const_strref;

class string_lit
 : public const_strref
{
public:
	template <std::size_t Size>
	string_lit(const_value_type (&lit)[Size])
	 : const_strref(lit, Size)
	{ }
};

} // namespace base
} // namespace EAGine

#endif //include guard

