/**
 *  @file eagine/math/config.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_CONFIG_1412201321_HPP
#define EAGINE_MATH_CONFIG_1412201321_HPP

// EAGINE_MATH_FAST_MAT_MULT_TRIVIAL
#ifndef EAGINE_MATH_FAST_MAT_MULT_TRIVIAL
# if defined(__GNUC__)
#  if __OPTIMIZE__
#   define EAGINE_MATH_FAST_MAT_MULT_TRIVIAL 1
#  else
#   define EAGINE_MATH_FAST_MAT_MULT_TRIVIAL 0
#  endif
# else
#  define EAGINE_MATH_FAST_MAT_MULT_TRIVIAL 0
# endif
#endif

// EAGINE_NO_MATH_VECTOR_SWIZZLES
#ifndef EAGINE_NO_MATH_VECTOR_SWIZZLES
#define EAGINE_NO_MATH_VECTOR_SWIZZLES 0
#endif

#endif //include guard

