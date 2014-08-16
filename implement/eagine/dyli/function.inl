/**
 *  @file eagine/dyli/function.inl
 *  @brief Dynamic library function utilities
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
namespace detail {

EAGINE_LIB_FUNC
std::shared_ptr<base::dynamic_library>
require_lib(const std::weak_ptr<base::dynamic_library>& wlib)
{
	base::shared_ptr<base::dynamic_library> lib = wlib.lock();

	if(!bool(lib))
	{
		throw base::runtime_error(base::string(base::translate(
			"Required dynamic library is not loaded"
		)));
	}

	return base::move(lib);
}

} // namespace detail
} // namespace base
} // namespace EAGine


