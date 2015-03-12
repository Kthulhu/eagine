/**
 *  @file eagine/vect/config.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_CONFIG_1308281038_HPP
#define EAGINE_VECT_CONFIG_1308281038_HPP

#ifndef EAGINE_USE_SIMD

# if defined(__clang__) || defined(__GNUC__)
# define EAGINE_USE_SIMD __SSE__
# else
# define EAGINE_USE_SIMD 1
# endif

#endif

#endif //include guard

