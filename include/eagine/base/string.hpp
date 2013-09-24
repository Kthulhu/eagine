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

	static Char* _empty_c_str(void)
	{
		static Char c = Char('\0');
		return &c;
	}

	template <typename Char_, typename CharTraits_>
	Char* _init_by_string(const std::basic_string<Char_, CharTraits_>& s)
	{
		if(s.empty()) return _empty_c_str();
		else return const_cast<Char*>(s.data());
	}
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
	 : _ptr(_empty_c_str())
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
		basic_string_ref<Char_>& that,
		typename std::enable_if<
			std::is_convertible<Char_, Char>::value &&
			!std::is_same<Char_, Char>::value
		>::type* = nullptr
	): _ptr(that.data())
	 , _len(that.size())
	{ }

	template <typename Char_, typename CharTraits_>
	basic_string_ref(
		const ::std::basic_string<Char_, CharTraits_>& s,
		typename std::enable_if<
			std::is_same<
				typename std::add_const<Char_>::type,
				Char
			>::value &&
			std::is_const<Char>::value
		>::type* = nullptr
	): _ptr(_init_by_string(s))
	 , _len(s.size())
	{ }

	template <typename Char_, typename CharTraits_>
	basic_string_ref(
		::std::basic_string<Char_, CharTraits_>& s,
		typename std::enable_if<
			std::is_same<Char, Char_>::value &&
			!std::is_const<Char>::value
		>::type* = nullptr
	): _ptr(_init_by_string(s))
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

	bool empty(void) const
	{
		return _len == 0;
	}

	size_type size(void) const
	{
		return _len;
	}

	size_type length(void) const
	{
		return _len;
	}

	value_type* data(void)
	{
		return _ptr;
	}

	string_type str(void) const
	{
		return string_type(_ptr, _len);
	}

	iterator begin(void)
	{
		return _ptr;
	}

	const_iterator begin(void) const
	{
		return _ptr;
	}

	iterator end(void)
	{
		return _ptr+_len;
	}

	const_iterator end(void) const
	{
		return _ptr+_len;
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

