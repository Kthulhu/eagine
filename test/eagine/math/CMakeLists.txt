#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

eagine_test_dir()

eagine_exec_test(angle)

eagine_exec_test_sse(scalar)
eagine_exec_test_nosse(scalar)

eagine_exec_test_sse(vector)
eagine_exec_test_nosse(vector)
eagine_exec_test_sse(tvec)
eagine_exec_test_nosse(tvec)

eagine_exec_test_sse(vector_swizzles)
eagine_exec_test_nosse(vector_swizzles)

eagine_exec_test_sse(quaternion)
eagine_exec_test_nosse(quaternion)

eagine_exec_test_sse(matrix1)
eagine_exec_test_nosse(matrix1)
eagine_exec_test_sse(matrix2)
eagine_exec_test_nosse(matrix2)
eagine_exec_test_sse(matrix3)
eagine_exec_test_nosse(matrix3)
eagine_exec_test_sse(matrix4)
eagine_exec_test_nosse(matrix4)

eagine_exec_test_sse(matrix_ctrs1)
eagine_exec_test_nosse(matrix_ctrs1)
eagine_exec_test_sse(matrix_ctrs2)
eagine_exec_test_nosse(matrix_ctrs2)
eagine_exec_test_sse(matrix_ctrs3)
eagine_exec_test_nosse(matrix_ctrs3)

eagine_exec_test_sse(tmat)
eagine_exec_test_nosse(tmat)
