/**
 *  @file eagine/base/assert.hpp
 *  @brief Assertions
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ASSERT_1408161720_HPP
#define EAGINE_BASE_ASSERT_1408161720_HPP

#include <cassert>

#define EAGINE_ABORT(MSG) assert(!bool(MSG))

#endif //include guard

