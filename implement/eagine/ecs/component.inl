/**
 *  @file eagine/ecs/component.inl
 *  @brief Implementation component-related functions
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>


namespace EAGine {
namespace ecs {
//------------------------------------------------------------------------------
// component_uid_getter::_curr_uid
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
component_uid&
component_uid_getter::_curr_uid(void)
{
	static component_uid uid = 0;
	return uid;
}
//------------------------------------------------------------------------------
// component_uid_getter::_new_uid
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
component_uid
component_uid_getter::new_uid(void)
{
	return _curr_uid()++;
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace EAGine


