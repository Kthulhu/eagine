/**
 *  @file eagine/base/vector.hpp
 *  @brief Dynamically allocated vector.
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_VECTOR_1308281038_HPP
#define EAGINE_BASE_VECTOR_1308281038_HPP

#include <vector>
#include <eagine/base/alloc.hpp>

namespace eagine {
namespace base {

template <typename T, typename Alloc = allocator<T>>
using vector = ::std::vector<T, Alloc>;

} // namespace base
} // namespace eagine

#endif //include guard

