#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

project(EAGine)

# the list of third-party libraries to link to
set(EAGINE_THIRD_PARTY_LIBRARIES "")

# compiler options
include(config/Compiler.cmake)
include(config/CPP.cmake)
# Boost
include(config/FindBoost.cmake)

configure_file(
	${PROJECT_SOURCE_DIR}/config/eagine/site_config.hpp.in
	${PROJECT_BINARY_DIR}/include/eagine/site_config.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/implement)

add_subdirectory(source)
add_subdirectory(test)
