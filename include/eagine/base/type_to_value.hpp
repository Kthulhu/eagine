/**
 *  @file eagine/base/type_to_value.hpp
 *  @brief Static container similar to tuple mapping unique types to values.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_TYPE_TO_VALUE_1308281038_HPP
#define EAGINE_BASE_TYPE_TO_VALUE_1308281038_HPP

#include <eagine/meta/instead_of.hpp>

namespace EAGine {
namespace base {

template <typename Value, typename Key>
struct type_to_value_unit
{
	Value _value;

	type_to_value_unit(Value value)
	 : _value(value)
	{ }
};

template <typename Value, typename ... Keys>
struct type_to_value
 : type_to_value_unit<Value, Keys>...
{
	type_to_value(
		typename meta::instead_of<Keys, Value>::type ... values
	): type_to_value_unit<Value, Keys>(values)...
	{ }

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
	Value& get(void)
	{
		return unit<Key>()._value;
	}

	template <typename Key>
	const Value& get(void) const
	{
		return unit<Key>()._value;
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

