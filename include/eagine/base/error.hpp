/**
 *  @file eagine/base/error.hpp
 *  @brief Base exception classes.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ERROR_1308281038_HPP
#define EAGINE_BASE_ERROR_1308281038_HPP

#include <stdexcept>
#include <system_error>

namespace EAGine {
namespace base {

using ::std::exception;
using ::std::runtime_error;
using ::std::system_error;
using ::std::throw_with_nested;
using ::std::rethrow_if_nested;

} // namespace base
} // namespace EAGine

#endif //include guard

