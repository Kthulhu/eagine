/**
 *  @file eagine/ecs/entity.hpp
 *  @brief Entity-related functions
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_ENTITY_1408161720_HPP
#define EAGINE_ECS_ENTITY_1408161720_HPP

namespace EAGine {
namespace ecs {

template <typename Entity>
inline Entity nil_entity(void)
{
	return Entity::nil();
}

} // namespace ecs
} // namespace EAGine

#endif //include guard

