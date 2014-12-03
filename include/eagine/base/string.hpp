/**
 *  @file eagine/base/string.hpp
 *  @brief UTF-8 encoded string and string references.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_STRING_1308281038_HPP
#define EAGINE_BASE_STRING_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/identity.hpp>
#include <eagine/base/alloc.hpp>
#include <eagine/base/array.hpp>
#include <eagine/base/vector.hpp>
#include <iosfwd>
#include <string>
#include <cstring>
#include <cassert>

namespace eagine {
namespace base {

// is_ext_char_string
template <typename Char, typename X>
struct is_ext_char_string
 : meta::false_type
{ };

// is_char_string
template <typename Char, typename X>
struct is_char_string
 : meta::false_type
{ };

// char_string_traits
template <typename X>
struct char_string_traits
{
	typedef void value_type;
};

// is_ext_char_string_any_const
template <typename Char, typename X>
struct is_ext_char_string_any_const
 : meta::integral_constant<
	bool,
	is_ext_char_string<
		typename meta::add_const<Char>::type, X
	>::value || is_ext_char_string<
		typename meta::remove_const<Char>::type, X
	>::value
> { };

// is_char_string_any_const
template <typename Char, typename X>
struct is_char_string_any_const
 : meta::integral_constant<
	bool,
	is_char_string<
		typename meta::add_const<Char>::type, X
	>::value || is_char_string<
		typename meta::remove_const<Char>::type, X
	>::value
> { };

// are_char_strings_any_const
template <typename Char, typename ... XN>
struct are_char_strings_any_const;

// are_char_strings_any_const
template <typename Char, typename X1>
struct are_char_strings_any_const<Char, X1>
 : is_char_string_any_const<Char, X1>
{ };

// are_char_strings_any_const
template <typename Char, typename X1, typename X2, typename ... XN>
struct are_char_strings_any_const<Char, X1, X2, XN...>
 : meta::integral_constant<
	bool,
	is_char_string_any_const<Char, X1>::value &&
	are_char_strings_any_const<Char, X2, XN...>::value
>
{ };

// is_string
template <typename X>
struct is_string
 : is_char_string<
	typename char_string_traits<X>::value_type, X
>{ };


// is_char_string<array>
template <typename Char, std::size_t N>
struct is_char_string<
	Char, array<Char, N>
>: meta::true_type
{ };

// char_string_traits<array>
template <typename Char, std::size_t N>
struct char_string_traits<array<Char, N>>
{
	typedef Char value_type;
};

// basic_string
template <
	typename Char,
	typename CharTraits = std::char_traits<Char>,
	typename Alloc = allocator<Char>
> using basic_string = ::std::basic_string<Char, CharTraits, Alloc>;

// string
typedef basic_string<char> string;

// is_ext_char_string<basic_string>
template <typename Char, typename Alloc>
struct is_ext_char_string<
	Char, basic_string<Char, std::char_traits<Char>, Alloc>
>: meta::true_type
{ };

// is_char_string<basic_string>
template <typename Char, typename Alloc>
struct is_char_string<
	Char, basic_string<Char, std::char_traits<Char>, Alloc>
>: meta::true_type
{ };

// char_string_traits<basic_string>
template <typename Char, typename Alloc>
struct char_string_traits<
	basic_string<Char, std::char_traits<Char>, Alloc>
>
{
	typedef Char value_type;
};

// basic_string_ref
template <typename Char>
class basic_string_ref;

// is_char_string<basic_string_ref>
template <typename Char>
struct is_char_string<
	Char, basic_string_ref<Char>
>: meta::true_type
{ };

// char_string_traits<basic_string_ref>
template <typename Char>
struct char_string_traits<basic_string_ref<Char>>
{
	typedef Char value_type;
};

// basic_lim_string
template <typename Char, std::size_t N>
class basic_lim_string;

// is_char_string<basic_lim_string>
template <typename Char, std::size_t N>
struct is_char_string<
	Char, basic_lim_string<Char, N>
>: meta::true_type
{ };

// char_string_traits<basic_lim_string>
template <typename Char, std::size_t N>
struct char_string_traits<basic_lim_string<Char, N>>
{
	typedef Char value_type;
};

// basic_lim_string
template <typename Char, std::size_t N>
class basic_lim_string
{
private:
	array<Char, N+1> _str;
	std::size_t _len;

	static std::size_t _min(std::size_t n1, std::size_t n2)
	noexcept
	{
		return n1<n2?n1:n2;
	}

	template <typename Char_>
	std::size_t _copy_from(Char_* cstr, std::size_t len)
	noexcept
	{
		len = _min(N, len);
		std::copy(cstr, cstr+len, _str.begin());
		_str[len] = Char(0);
		return len;
	}
public:
	typedef Char value_type;
	typedef typename meta::add_const<value_type>::type const_value_type;
	typedef typename meta::remove_const<value_type>::type nonconst_value_type;

	constexpr basic_lim_string(void)
	noexcept
	 : _len(0)
	{ }

	template <
		typename ... Char_,
		typename = typename meta::enable_if<
			sizeof ... (Char_) <= N
		>::type
	>
	constexpr basic_lim_string(Char_ ... c)
	noexcept
	 : _str{{Char(c)...}}
	 , _len(sizeof ... (Char_))
	{ }

	constexpr basic_lim_string(const basic_lim_string& that)
	noexcept
	 : _str(that._str)
	 , _len(that._len)
	{ }

	basic_lim_string(basic_lim_string&& tmp)
	noexcept
	 : _str(std::move(tmp._str))
	 , _len(tmp._len)
	{ }

	basic_lim_string(const basic_string_ref<Char>& str)
	noexcept;

	basic_lim_string(const basic_string_ref<const Char>& str)
	noexcept;

	basic_lim_string& operator = (const basic_string_ref<Char>& str)
	noexcept;

	basic_lim_string& operator = (const basic_string_ref<const Char>& str)
	noexcept;

	static constexpr
	std::size_t capacity(void)
	{
		return N;
	}

	bool empty(void) const
	noexcept
	{
		return _len == 0u;
	}

	std::size_t size(void) const
	noexcept
	{
		return _len;
	}

	basic_string<Char>
	str(void) const
	{
		return basic_string<Char>(_str.data(), _len);
	}

	basic_string<Char>
	str(const typename basic_string<Char>::allocator_type& alloc) const
	{
		return basic_string<Char>(_str.data(), _len, alloc);
	}

	const_value_type*
	c_str(void) const
	noexcept
	{
		return _str.data();
	}

	value_type*
	data(void)
	noexcept
	{
		return _str.data();
	}

	const_value_type*
	data(void) const
	noexcept
	{
		return _str.data();
	}

	typedef typename array<Char, N>::iterator iterator;
	typedef typename array<Char, N>::const_iterator const_iterator;

	iterator begin(void) const
	noexcept
	{
		return _str.begin();
	}

	iterator end(void) const
	noexcept
	{
		return _str.begin()+_len;
	}
};

// lim_string
template <std::size_t N>
using lim_string = basic_lim_string<char, N>;

// basic_const_var_string
template <typename Char, typename Size>
struct basic_const_var_string;

// is_char_string<basic_const_var_string>
template <typename Char, typename Size>
struct is_char_string<
	Char, basic_const_var_string<Char, Size>
>: meta::true_type
{ };

// char_string_traits<basic_const_var_string>
template <typename Char, typename Size>
struct char_string_traits<basic_const_var_string<Char, Size>>
{
	typedef Char value_type;
};

// basic_const_var_string
template <typename Char, typename Size>
struct basic_const_var_string
{
private:
	const Size _size = 0;
	const Char _data[1] = { '\0' };
public:
	bool empty(void) const
	noexcept
	{
		return _size == 0;
	}

	std::size_t size(void) const
	noexcept
	{
		return _size;
	}

	const Char* data(void) const
	noexcept
	{
		return _data;
	}
};

// cvarstr
typedef basic_const_var_string<char, std::uint32_t> cvarstr;

// basic_string_ref
template <typename Char>
class basic_string_ref
{
private:
	Char* _ptr;
	std::size_t _len;

	typedef const basic_string_ref& pcself;

	static Char* _empty_c_str(void)
	noexcept
	{
		static Char c = Char('\0');
		return &c;
	}

	Char* _init_by_string(const string& s)
	noexcept
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

	typedef basic_string<nonconst_value_type> string_type;

	basic_string_ref(void)
	noexcept
	 : _ptr(_empty_c_str())
	 , _len(0)
	{ }

	explicit basic_string_ref(value_type* ptr)
	noexcept
	 : _ptr(ptr)
	 , _len(::std::strlen(ptr))
	{ }

	basic_string_ref(value_type* ptr, size_type len)
	noexcept
	 : _ptr(ptr)
	 , _len(len)
	{ }

	template <typename Char_, std::size_t Len>
	basic_string_ref(
		Char_ (&lit)[Len],
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	) noexcept
	 : _ptr(lit)
	 , _len(lit[Len-1]?Len:Len-1)
	{ }

	basic_string_ref(const basic_string_ref& that)
	noexcept
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
	) noexcept
	 : _ptr(that.data())
	 , _len(that.size())
	{ }

	template <typename Char_, typename CharTraits_>
	basic_string_ref(
		const basic_string<Char_, CharTraits_>& s,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	) noexcept
	 : _ptr(_init_by_string(s))
	 , _len(s.size())
	{ }

	template <typename Char_, typename CharTraits_>
	basic_string_ref(
		basic_string<Char_, CharTraits_>& s,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	) noexcept
	 : _ptr(_init_by_string(s))
	 , _len(s.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		const basic_lim_string<Char_, N>& ls,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	) noexcept
	 : _ptr(ls.data())
	 , _len(ls.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		basic_lim_string<Char_, N>& ls,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	) noexcept
	 : _ptr(ls.data())
	 , _len(ls.size())
	{ }

	template <typename Char_, typename Size_>
	basic_string_ref(
		const basic_const_var_string<Char_, Size_>& vs,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	) noexcept
	 : _ptr(vs.data())
	 , _len(vs.size())
	{ }

	template <typename Char_, typename Allocator_>
	basic_string_ref(
		const ::std::vector<Char_, Allocator_>& v,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	) noexcept
	 : _ptr(v.data())
	 , _len(v.size())
	{ }

	template <typename Char_, typename Allocator_>
	basic_string_ref(
		::std::vector<Char_, Allocator_>& v,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	) noexcept
	 : _ptr(v.data())
	 , _len(v.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		const array<Char_, N>& a,
		typename meta::enable_if<_compatible<const Char_>::value>::type* = 0
	) noexcept
	 : _ptr(a.data())
	 , _len(a.size())
	{ }

	template <typename Char_, std::size_t N>
	basic_string_ref(
		array<Char_, N>& a,
		typename meta::enable_if<_compatible<Char_>::value>::type* = 0
	) noexcept
	 : _ptr(a.data())
	 , _len(a.size())
	{ }

	basic_string_ref& operator = (const basic_string_ref& that)
	noexcept
	{
		this->_ptr = that._ptr;
		this->_len = that._len;
		return *this;
	}

	bool in(void) const
	noexcept
	{
		return false;
	}

	template <typename ... P>
	bool in(pcself sr0, P&& ... sri) const
	noexcept
	{
		return (*this == sr0) || in(std::forward<P>(sri)...);
	}

	bool empty(void) const
	noexcept
	{
		return _len == 0;
	}

	size_type size(void) const
	noexcept
	{
		return _len;
	}

	size_type length(void) const
	noexcept
	{
		return _len;
	}

	bool null_terminated(void) const
	noexcept
	{
		return _ptr[_len] == '\0';
	}

	value_type* data(void)
	noexcept
	{
		return _ptr;
	}

	const_value_type*
	data(void) const
	noexcept
	{
		return _ptr;
	}

	string_type str(void) const
	{
		return string_type(_ptr, _len);
	}

	string_type str(const typename string_type::allocator_type& alloc) const
	{
		return string_type(_ptr, _len, alloc);
	}

	iterator begin(void)
	noexcept
	{
		return _ptr;
	}

	const_iterator begin(void) const
	noexcept
	{
		return _ptr;
	}

	iterator end(void)
	noexcept
	{
		return _ptr+_len;
	}

	const_iterator end(void) const
	noexcept
	{
		return _ptr+_len;
	}

	reference at(std::size_t pos) const
	noexcept
	{
		assert(pos < _len);
		return _ptr[pos];
	}

	reference operator [](std::size_t pos) const
	noexcept
	{
		return at(pos);
	}

	reference front(void) const
	noexcept
	{
		return at(0);
	}

	reference back(void) const
	noexcept
	{
		return at(_len-1);
	}
};

// string_ref
typedef basic_string_ref<char> string_ref;
// const_string_ref
typedef basic_string_ref<const char> const_string_ref;

// strref
typedef string_ref strref;
// cstrref
typedef const_string_ref cstrref;

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>::
basic_lim_string(const basic_string_ref<Char>& bsr)
noexcept
 : _len(_copy_from(bsr.data(), bsr.size()))
{ }

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>::
basic_lim_string(const basic_string_ref<const Char>& bsr)
noexcept
 : _len(_copy_from(bsr.data(), bsr.size()))
{ }

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>&
basic_lim_string<Char, N>::
operator = (const basic_string_ref<Char>& bsr)
noexcept
{
	_len = _copy_from(bsr.data(), bsr.size());
	return *this;
}

template <typename Char, std::size_t N>
inline
basic_lim_string<Char, N>&
basic_lim_string<Char, N>::
operator = (const basic_string_ref<const Char>& bsr)
noexcept
{
	_len = _copy_from(bsr.data(), bsr.size());
	return *this;
}


// detail
namespace detail {

// are_bin_op_char_strings
template <typename Char, typename X1, typename X2>
struct are_bin_op_char_strings
 : meta::integral_constant<
	bool,
	are_char_strings_any_const<Char, X1, X2>::value && !(
		is_ext_char_string_any_const<Char, X1>::value &&
		is_ext_char_string_any_const<Char, X2>::value
	)
>
{ };

// are_bin_op_strings
template <typename X1, typename X2>
struct are_bin_op_strings
 : are_bin_op_char_strings<
	typename char_string_traits<X1>::value_type,
	X1, X2
>
{ };

} // namespace detail

// operator == (S1, S2)
template <typename S1, typename S2>
inline
typename meta::enable_if<
	detail::are_bin_op_strings<S1, S2>::value,
	bool
>::type operator == (const S1& s1, const S2& s2)
noexcept
{
	if(s1.size() != s2.size())
	{
		return false;
	}

	typedef std::char_traits<
		typename char_string_traits<S1>::value_type
	> cht;

	return cht::compare(s1.data(), s2.data(), s1.size()) == 0;
}

// operator != (S1, S2)
template <typename S1, typename S2>
inline
typename meta::enable_if<
	detail::are_bin_op_strings<S1, S2>::value,
	bool
>::type operator != (const S1& s1, const S2& s2)
noexcept
{
	if(s1.size() != s2.size())
	{
		return true;
	}

	typedef std::char_traits<
		typename char_string_traits<S1>::value_type
	> cht;

	return cht::compare(s1.data(), s2.data(), s1.size()) != 0;
}

// operator <  (S1, S2)
template <typename S1, typename S2>
inline
typename meta::enable_if<
	detail::are_bin_op_strings<S1, S2>::value,
	bool
>::type operator <  (const S1& s1, const S2& s2)
noexcept
{
	typedef std::char_traits<
		typename char_string_traits<S1>::value_type
	> cht;

	std::size_t s1s = s1.size();
	std::size_t s2s = s2.size();

	std::ptrdiff_t lcmp = s1s - s2s;
	int scmp = cht::compare(s1.data(), s2.data(), s1s<s2s?s1s:s2s);

	return (scmp < 0) || ((scmp == 0) && (lcmp < 0));
}

// operator >  (S1, S2)
template <typename S1, typename S2>
inline
typename meta::enable_if<
	detail::are_bin_op_strings<S1, S2>::value,
	bool
>::type operator >  (const S1& s1, const S2& s2)
noexcept
{
	typedef std::char_traits<
		typename char_string_traits<S1>::value_type
	> cht;

	std::size_t s1s = s1.size();
	std::size_t s2s = s2.size();

	std::ptrdiff_t lcmp = s1s - s2s;
	int scmp = cht::compare(s1.data(), s2.data(), s1s<s2s?s1s:s2s);

	return (scmp > 0) || ((scmp == 0) && (lcmp > 0));
}

// operator <= (S1, S2)
template <typename S1, typename S2>
inline
typename meta::enable_if<
	detail::are_bin_op_strings<S1, S2>::value,
	bool
>::type operator <= (const S1& s1, const S2& s2)
noexcept
{
	typedef std::char_traits<
		typename char_string_traits<S1>::value_type
	> cht;

	std::size_t s1s = s1.size();
	std::size_t s2s = s2.size();

	std::ptrdiff_t lcmp = s1s - s2s;
	int scmp = cht::compare(s1.data(), s2.data(), s1s<s2s?s1s:s2s);

	return (scmp < 0) || ((scmp == 0) && (lcmp <= 0));
}

// operator >= (S1, S2)
template <typename S1, typename S2>
inline
typename meta::enable_if<
	detail::are_bin_op_strings<S1, S2>::value,
	bool
>::type operator >= (const S1& s1, const S2& s2)
noexcept
{
	typedef std::char_traits<
		typename char_string_traits<S1>::value_type
	> cht;

	std::size_t s1s = s1.size();
	std::size_t s2s = s2.size();

	std::ptrdiff_t lcmp = s1s - s2s;
	int scmp = cht::compare(s1.data(), s2.data(), s1s<s2s?s1s:s2s);

	return (scmp > 0) || ((scmp == 0) && (lcmp >= 0));
}

// operator <<
template <typename Char, typename StrCtr>
inline
typename meta::enable_if<
	is_char_string_any_const<Char, StrCtr>::value &&
	!is_ext_char_string_any_const<Char, StrCtr>::value,
	std::basic_ostream<Char>&
>::type
operator << (
	std::basic_ostream<Char>& out,
	const StrCtr& sref
)
{
	return out.write(sref.data(), sref.size());
}

} // namespace base
} // namespace eagine

namespace std {

// std::hash<string>
template <>
struct hash<eagine::base::string>
{
	typedef eagine::base::string argument_type;
	typedef size_t result_type;

	size_t operator()(const eagine::base::string& s) const
	noexcept
	{
#ifdef _HASH_BYTES_H
		return std::_Hash_impl::hash(s.data(), s.length());
#else
		return std::hash<const char*>()(s.data());
#endif
	}
};

} // namespace std

#endif //include guard

