/**
 *  @file eagine/meta/instead_of.hpp
 *  @brief The instead_of metafunction
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_INSTEAD_OF_1308281038_HPP
#define EAGINE_META_INSTEAD_OF_1308281038_HPP

namespace eagine {
namespace meta {

template <typename Src, typename Dst>
struct instead_of
{
	typedef Dst type;

	static constexpr inline
	Dst value(Dst val)
	{
		return val;
	}
};

} // namespace meta
} // namespace eagine

#endif //include guard

