#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

function(eagine_vect_exec_test TEST_NAME)
	eagine_exec_test_sse("${TEST_NAME}")
	eagine_exec_test_nosse("${TEST_NAME}")
endfunction()

eagine_vect_exec_test(data)
eagine_vect_exec_test(fill)
eagine_vect_exec_test(axis)
eagine_vect_exec_test(from)
eagine_vect_exec_test(hsum)
eagine_vect_exec_test(shuffle)
eagine_vect_exec_test(compare)
eagine_vect_exec_test(lerp)
