#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

eagine_exec_test(angle)

eagine_exec_test_sse(vector)
eagine_exec_test_nosse(vector)
eagine_exec_test_sse(tvec)
eagine_exec_test_nosse(tvec)

eagine_exec_test_sse(matrix1)
eagine_exec_test_nosse(matrix1)
