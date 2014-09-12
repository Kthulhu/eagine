/**
 *  @file eagine/dyli/loader.inl
 *  @brief Implementation of dynamic library loader functionality
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#include <eagine/base/error.hpp>

namespace EAGine {
namespace dyli {

EAGINE_LIB_FUNC
library loader::main_exe(void)
{
	return library(base::make_shared<base::executable_module>());
}

EAGINE_LIB_FUNC
library loader::load(base::cstrref path)
{
	return library(base::make_shared<base::dynamic_library>(path));
}

EAGINE_LIB_FUNC
library loader::try_load(base::cstrref path)
{
	try
	{
		return load(path);
	}
	catch(base::runtime_error&)
	{
		return library();
	}
}

} // namespace dyli
} // namespace EAGine


