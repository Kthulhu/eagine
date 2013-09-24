#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.42.0)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRECTORIES})
	set(BOOST_UUID_FOUND 1)
	message(STATUS "Basic Boost libraries found")
else()
	set(BOOST_UUID_FOUND 0)
	message(FATAL_ERROR "Boost Uuid library is required")
endif()

find_package(Boost 1.48.0 COMPONENTS locale)
if(Boost_FOUND)
	set(BOOST_LOCALE_FOUND 1)
	set(EAGINE_THIRD_PARTY_LIBRARIES "${Boost_LIBRARIES}:${EAGINE_THIRD_PARTY_LIBRARIES}")
	message(STATUS "Boost Locale library found")
else()
	set(BOOST_LOCALE_FOUND 0)
endif()
