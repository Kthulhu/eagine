/**
 *  @file eagine/base/string.hpp
 *  @brief UTF-8 encoded string and string references.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_STRING_1308281038_HPP
#define EAGINE_BASE_STRING_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <vector>
#include <array>
#include <string>
#include <cstring>
#include <type_traits>

namespace EAGine {
namespace base {

using ::std::string;

template <typename Char>
class basic_string_ref;

template <typename Char, std::size_t N>
class basic_lim_string
{
private:
	std::array<Char, N+1> _str;
	std::size_t _len;

	static std::size_t _min(std::size_t n1, std::size_t n2)
	{
		return n1<n2?n1:n2;
	}

	template <typename Char_>
	std::size_t _copy_from(Char_* str, std::size_t len)
	{
		len = _min(N, len);
		std::copy(str, str+len, _str.begin());
		_str[len] = Char(0);
		return len;
	}
public:
	typedef Char value_type;
	typedef typename meta::add_const<value_type>::type const_value_type;
	typedef typename meta::remove_const<value_type>::type nonconst_value_type;

	basic_lim_string(void)
	 : _len(0)
	{ }

	basic_lim_string(const basic_lim_string& that)
	 : _str(that._str)
	 , _len(that._len)
	{ }

	basic_lim_string(basic_lim_string&& tmp)
	 : _str(std::move(tmp._str))
	 , _len(tmp._len)
	{ }

	basic_lim_string(const basic_string_ref<Char>& str);
	basic_lim_string(const basic_string_ref<const Char>& str);

	basic_lim_string& operator = (const basic_string_ref<Char>& str);
	basic_lim_string& operator = (const basic_string_ref<const Char>& str);

	bool empty(void) const
	{
		return _len == 0u;
	}

	std::size_t size(void) const
	{
		return _len;
	}

	const_value_type*
	c_str(void) const
	{
		return _str.data();
	}

	value_type*
	data(void)
	{
		return _str.data();
	}

	const_value_type*
	data(void) const
	{
		return _str.data();
	}

	typedef typename std::array<Char, N>::iterator iterator;
	typedef typename std::array<Char, N>::const_iterator const_iterator;

	iterator begin(void)
	{
		return _str.begin();
	}

	iterator end(void)
	{
		return _str.begin()+_len;
	}
};

template <std::size_t N>
using lim_string = basic_lim_string<char, N>;

template <typename Char>
struct basic_const_var_string
{
private:
	std::uint32_t _size = 0;
	const Char _data[1] = { '\0' };
public:
	bool empty(void) const
	{
		return _size == 0;
	}

	std::size_t size(void) const
	{
		return _size;
	}

	const Char* data(void) const
	{
		return _data;
	}
};

typedef basic_const_var_string<char> cvarstr;

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

	Char* _init_by_string(const string& s)
	{
		if(s.empty()) return _empty_c_str();
		else return const_cast<Char*>(s.data());
	}

	template <typename Char_>
	struct _compatible
	 : meta::integral_constant<
		bool,
		meta::is_same<Char, Char_>::value ||
		meta::is_same<
			typename meta::add_const<Char_>::type,
			Char
		>::value
	>
	{ };
public:
	typedef Char value_type;
	typedef typename meta::add_const<value_type>::type const_value_type;
	typedef typename meta::remove_const<value_type>::type nonconst_value_type;

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

	template <std::size_t Len>
	basic_string_ref(const_value_type (&lit)[Len])
	 : _ptr(lit)
	 , _len(Len-1)
	{ }

	basic_string_ref(const basic_string_ref& that)
	 : _ptr(that._ptr)
	 , _len(that._len)
	{ }

	template <typename Char_>
	basic_string_ref(
		basic_string_ref<Char_>& that,
		typename meta::enable_if<
			meta::is_convertible<Char_, Char>::value &&
			!meta::is_same<Char_, Char>::value
		>::type* = nullptr
	): _ptr(that.data())
	 , _len(that.size())
	{ }

	template <typename Char_, typename CharTraits_>
	basic_string_ref(
		const ::std::basic_string<Char_, CharTraits_>& s,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	): _ptr(_init_by_string(s))
	 , _len(s.size())
	{ }

	template <typename Char_, typename CharTraits_>
	basic_string_ref(
		::std::basic_string<Char_, CharTraits_>& s,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	): _ptr(_init_by_string(s))
	 , _len(s.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		const basic_lim_string<Char_, N>& ls,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	): _ptr(ls.data())
	 , _len(ls.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		basic_lim_string<Char_, N>& ls,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	): _ptr(ls.data())
	 , _len(ls.size())
	{ }

	template <typename Char_>
	basic_string_ref(
		const basic_const_var_string<Char_>& vs,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	): _ptr(vs.data())
	 , _len(vs.size())
	{ }

	template <typename Char_, typename Allocator_>
	basic_string_ref(
		const ::std::vector<Char_, Allocator_>& v,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	): _ptr(v.data())
	 , _len(v.size())
	{ }

	template <typename Char_, typename Allocator_>
	basic_string_ref(
		::std::vector<Char_, Allocator_>& v,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	): _ptr(v.data())
	 , _len(v.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		const ::std::array<Char_, N>& a,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	): _ptr(a.data())
	 , _len(a.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		::std::array<Char_, N>& a,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	): _ptr(a.data())
	 , _len(a.size())
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

	bool null_terminated(void) const
	{
		return _ptr[_len] == '\0';
	}

	value_type* data(void)
	{
		return _ptr;
	}

	const_value_type*
	data(void) const
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
typedef basic_string_ref<const char> const_string_ref;

typedef string_ref strref;
typedef const_string_ref cstrref;

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>::
basic_lim_string(const basic_string_ref<Char>& str)
 : _len(_copy_from(str.data(), str.size()))
{ }

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>::
basic_lim_string(const basic_string_ref<const Char>& str)
 : _len(_copy_from(str.data(), str.size()))
{ }

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>&
basic_lim_string<Char, N>::
operator = (const basic_string_ref<Char>& str)
{
	_len = _copy_from(str.data(), str.size());
	return *this;
}

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>&
basic_lim_string<Char, N>::
operator = (const basic_string_ref<const Char>& str)
{
	_len = _copy_from(str.data(), str.size());
	return *this;
}

} // namespace base
} // namespace EAGine

#endif //include guard

