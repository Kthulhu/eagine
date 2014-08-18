/**
 *  @file eagine/dyli/detail.hpp
 *  @brief Dynamically linked library implementation details
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_DYLI_DETAIL_1408161720_HPP
#define EAGINE_DYLI_DETAIL_1408161720_HPP

#include <eagine/base/memory.hpp>
#include <eagine/base/dyn_lib.hpp>
#include <eagine/base/error.hpp>

namespace EAGine {
namespace dyli {
namespace detail {

std::shared_ptr<base::dynamic_library>
require_lib(const std::weak_ptr<base::dynamic_library>&);

} // namespace detail
} // namespace dyli
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/dyli/detail.inl>
#endif

#endif //include guard

