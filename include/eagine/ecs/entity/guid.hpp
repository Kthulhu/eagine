/**
 *  @file eagine/ecs/entity/guid.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_ENTITY_GUID_1408161720_HPP
#define EAGINE_ECS_ENTITY_GUID_1408161720_HPP

#include <eagine/ecs/entity.hpp>
#include <eagine/base/guid.hpp>
#include <cstring>
#include <cassert>

namespace EAGine {
namespace ecs {

template <>
struct entity_traits<base::guid>
{
	static inline
	base::guid nil(void)
	noexcept
	{
		return base::guid::nil();
	}

	static
	unsigned partition(const base::guid& g, unsigned n)
	noexcept
	{
		assert(n != 0);
		return g.data[0] % n;
	}

	static inline
	bool is_valid_string(const base::cstrref& s)
	noexcept
	{
		if(s.size() != 36) return false;

		static const char* h = "0123456789abcdefABCDEF";
		static const char* c = "-";
		static const char* m = "000000001000010000100001000000000000";
		static const char* x[2] = {h, c};

		for(unsigned i=0; i<36; ++i)
		{
			if(!std::strchr(x[int(m[i]-'0')], s[i]))
				return false;
		}
		return true;
	}

	static inline
	base::string to_string(const base::guid& g)
	{
		return g.to_string();
	}

	static inline
	base::guid from_string(const base::string& s)
	{
		return base::guid(s);
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

