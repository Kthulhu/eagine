/**
 *  @file eagine/dyli/library.inl
 *  @brief Implementation dynamic library functionality
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#include <eagine/base/error.hpp>
#include <eagine/base/locale.hpp>

namespace EAGine {
namespace dyli {

EAGINE_LIB_FUNC
library weak_lib::require(void) const
{
	return library(detail::require_lib(_wlib));
}

} // namespace base
} // namespace EAGine


