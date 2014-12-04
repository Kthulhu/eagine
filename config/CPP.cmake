#  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# we need C++11
if(${CMAKE_COMPILER_IS_GNUCXX})
	set(OGLPLUS_CPP11_COMPILER_SWITCH -std=c++1y)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(OGLPLUS_CPP11_COMPILER_SWITCH -std=c++1y)
endif()
# TODO add support for other compilers

add_definitions(${OGLPLUS_CPP11_COMPILER_SWITCH})

