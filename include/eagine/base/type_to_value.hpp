/**
 *  @file eagine/base/type_to_value.hpp
 *  @brief Static container similar to tuple mapping unique types to values.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_TYPE_TO_VALUE_1308281038_HPP
#define EAGINE_BASE_TYPE_TO_VALUE_1308281038_HPP

#include <eagine/meta/instead_of.hpp>
#include <utility>

namespace EAGine {
namespace base {

template <typename Value>
struct type_to_value_unit_base
{
	Value _value;

	type_to_value_unit_base(void) = default;

	template <typename T>
	type_to_value_unit_base(T&& value)
	 : _value(std::forward<T>(value))
	{ }
};

template <typename Value, typename Key>
struct type_to_value_unit
 : type_to_value_unit_base<Value>
{
	type_to_value_unit(void) = default;

	template <typename T>
	type_to_value_unit(T&& value)
	 : type_to_value_unit_base<Value>(std::forward<T>(value))
	{ }
};

template <typename Value, typename ... Keys>
struct type_to_value
 : type_to_value_unit<Value, Keys>...
{
	type_to_value(void) = default;

	type_to_value(
		typename meta::instead_of<Keys, Value>::type ... values
	): type_to_value_unit<Value, Keys>(values)...
	{ }

	type_to_value_unit_base<Value>& unit(std::size_t pos)
	{
		assert(pos < sizeof...(Keys));
		typedef type_to_value_unit_base<Value> ub_t;
		ub_t* units = (ub_t*)(void*)this;
		return units[pos];
	}

	const type_to_value_unit_base<Value>& unit(std::size_t pos) const
	{
		assert(pos < sizeof...(Keys));
		typedef type_to_value_unit_base<Value> ub_t;
		const ub_t* units = (const ub_t*)(const void*)this;
		return units[pos];
	}

	template <typename Key>
	type_to_value_unit<Value, Key>& unit(void)
	{
		return *this;
	}

	template <typename Key>
	const type_to_value_unit<Value, Key>& unit(void) const
	{
		return *this;
	}

	template <typename Key>
	Value& ref(void)
	{
		return unit<Key>()._value;
	}

	template <typename Key>
	const Value& ref(void) const
	{
		return unit<Key>()._value;
	}

	Value& ref(std::size_t pos)
	{
		return unit(pos)._value;
	}

	const Value& ref(std::size_t pos) const
	{
		return unit(pos)._value;
	}

	Value& operator [] (std::size_t pos)
	{
		return ref(pos);
	}

	const Value& operator [] (std::size_t pos) const
	{
		return ref(pos);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

