#  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
enable_testing()
include(CTest)

function(add_eagine_test TEST_NAME TEST_LIBRARIES BUILD_ONLY)

	add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)
	target_link_libraries(${TEST_NAME} ${TEST_LIBRARIES})
	target_link_libraries(${TEST_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

	add_test(
		build-test-${TEST_NAME}
		"${CMAKE_COMMAND}"
		--build ${CMAKE_BINARY_DIR}
		--target ${TEST_NAME}
	)

	if(NOT BUILD_ONLY)
		add_test(exec-test-${TEST_NAME} ${TEST_NAME})
		set_tests_properties(
			exec-test-${TEST_NAME}
			PROPERTIES DEPENDS
			build-test-${TEST_NAME}
		)
	endif()
endfunction()

function(eagine_build_test TEST_NAME)
	add_eagine_test("${TEST_NAME}" "${ARGN}" TRUE)
endfunction()

function(eagine_exec_test TEST_NAME)
	add_eagine_test("${TEST_NAME}" "${ARGN}" FALSE)
endfunction()

