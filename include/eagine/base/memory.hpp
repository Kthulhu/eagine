/**
 *  @file eagine/base/memory.hpp
 *  @brief Smart pointers
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_MEMORY_1408161723_HPP
#define EAGINE_BASE_MEMORY_1408161723_HPP

#include <memory>

namespace EAGine {
namespace base {

using ::std::weak_ptr;
using ::std::shared_ptr;
using ::std::unique_ptr;

using ::std::make_shared;

} // namespace base
} // namespace EAGine

#endif //include guard

