#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

include(./testing.cmake)

eagine_exec_test(math_close_to)

add_subdirectory(base)
add_subdirectory(vect)
add_subdirectory(unit)
add_subdirectory(math)
