#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

eagine_test_dir()

eagine_exec_test(tribool)
eagine_exec_test(utf8)

eagine_exec_test(alloc)

eagine_exec_test(array)
eagine_exec_test(string)

eagine_exec_test(memory_block)
eagine_exec_test(memory_buffer)
eagine_exec_test(memory_range)

eagine_exec_test(locale)
eagine_exec_test(format)
eagine_exec_test(guid)

eagine_exec_test(sim_clock)
