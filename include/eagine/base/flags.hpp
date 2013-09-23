/**
 *  @file eagine/base/flags.hpp
 *  @brief Basic flags.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_FLAGS_1308281038_HPP
#define EAGINE_BASE_FLAGS_1308281038_HPP

#include <type_traits>

namespace EAGine {
namespace base {

template <typename FlagEnum>
class flags
{
public:
	typedef typename std::underlying_type<FlagEnum>::type type;
private:
	type _flags;
public:
	flags(void)
	 : _flags(type(0))
	{ }

	flags(type initial)
	 : _flags(initial)
	{ }

	bool is_set(FlagEnum flag) const
	{
		return (_flags & type(flag)) == type(flag);
	}

	flags& set(FlagEnum flag)
	{
		_flags |= type(flag);
		return *this;
	}

	flags& clear(FlagEnum flag)
	{
		_flags &= ~type(flag);
		return *this;
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

