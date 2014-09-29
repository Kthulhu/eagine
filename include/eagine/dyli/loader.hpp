/**
 *  @file eagine/dyli/loader.hpp
 *  @brief Dynamic library loader.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DYLI_LOADER_1408161720_HPP
#define EAGINE_DYLI_LOADER_1408161720_HPP

#include <eagine/dyli/library.hpp>

namespace EAGine {
namespace dyli {

class loader
{
public:
	library main_exe(void);
	library load(base::cstrref path);
	library try_load(base::cstrref path);
};

} // namespace dyli
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/dyli/loader.inl>
#endif

#endif //include guard

