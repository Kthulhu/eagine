/**
 *  @file eagine/base/tribool.hpp
 *  @brief Tri-state logic
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_TRIBOOL_1308281038_HPP
#define EAGINE_BASE_TRIBOOL_1308281038_HPP

namespace eagine {
namespace base {

enum class _tribool_value_t : unsigned char
{
	_false = 0x00,
	_true = 0x01,
	_unknown = 0x02
};

struct indeterminate_t { };

constexpr static const indeterminate_t indeterminate = {};

class tribool;

class weakbool
{
private:
	typedef _tribool_value_t _value_t;
	_value_t _value;

	friend class tribool;

	constexpr explicit
	weakbool(_value_t value)
	noexcept
	 : _value(value)
	{ }
public:
	constexpr
	explicit 
	operator bool (void) const
	noexcept
	{
		return _value != _value_t::_false;
	}

	constexpr
	bool operator ! (void) const
	noexcept
	{
		return _value != _value_t::_true;
	}

	constexpr
	bool is(indeterminate_t) const
	{
		return _value == _value_t::_unknown;
	}
};

class tribool
{
private:
	typedef _tribool_value_t _value_t;
	_value_t _value;
public:
	constexpr
	tribool(void)
	noexcept
	 : _value(_value_t::_false)
	{ }

	constexpr
	tribool(bool value)
	noexcept
	 : _value(value?_value_t::_true:_value_t::_false)
	{ }

	constexpr
	tribool(indeterminate_t)
	noexcept
	 : _value(_value_t::_unknown)
	{ }

	constexpr
	explicit 
	operator bool (void) const
	noexcept
	{
		return _value == _value_t::_true;
	}

	constexpr
	bool operator ! (void) const
	noexcept
	{
		return _value == _value_t::_false;
	}

	constexpr
	bool operator * (void) const
	noexcept
	{
		return _value == _value_t::_unknown;
	}

	constexpr
	weakbool operator ~ (void) const
	noexcept
	{
		return weakbool(_value);
	}

	constexpr
	bool is(indeterminate_t) const
	noexcept
	{
		return *(*this);
	}

	friend
	constexpr
	tribool operator == (tribool a, tribool b)
	noexcept
	{
		return (*a || *b)?
			tribool{indeterminate}:
			tribool{a._value == b._value};
	}

	friend
	constexpr
	tribool operator != (tribool a, tribool b)
	noexcept
	{
		return (a.is(indeterminate) || b.is(indeterminate))?
			tribool{indeterminate}:
			tribool{a._value != b._value};
	}
};

constexpr inline
tribool operator && (tribool a, tribool b)
noexcept
{
	return !a?tribool{false}:a?b:!b?tribool{false}:tribool{indeterminate};
}

constexpr inline
tribool operator || (tribool a, tribool b)
noexcept
{
	return a?tribool{true}:!a?b:b?tribool{true}:tribool{indeterminate};
}

} // namespace base
} // namespace eagine

#endif //include guard

