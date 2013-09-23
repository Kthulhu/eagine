#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

macro(add_eagine_module MOD_NAME)
	file(GLOB LIB_${MOD_NAME}_SRC "${MOD_NAME}/*.cpp")
	add_library(${MOD_NAME} ${LIB_${MOD_NAME}_SRC})
endmacro()

add_eagine_module(base)
