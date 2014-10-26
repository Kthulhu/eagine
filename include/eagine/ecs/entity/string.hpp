/**
 *  @file eagine/ecs/entity/string.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_ENTITY_STRING_1408161720_HPP
#define EAGINE_ECS_ENTITY_STRING_1408161720_HPP

#include <eagine/ecs/entity.hpp>
#include <eagine/base/string.hpp>
#include <cassert>

namespace EAGine {
namespace ecs {

template <>
struct entity_traits<base::string>
{
	static inline
	base::string nil(void)
	noexcept
	{
		return base::string();
	}

	static
	unsigned partition(const base::string& s, unsigned n)
	noexcept
	{
		assert(n != 0);
		static std::hash<base::string> func;
		return func(s) % n;
	}

	static inline
	bool is_valid_string(const base::cstrref& s)
	noexcept
	{
		return !s.empty();
	}

	static inline
	const base::string& to_string(const base::string& s)
	{
		return s;
	}

	static inline
	const base::string& from_string(const base::string& s)
	{
		return s;
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

