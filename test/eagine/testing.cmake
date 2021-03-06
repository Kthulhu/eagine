#  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
enable_testing()
include(CTest)

macro(add_eagine_test TEST_NAME SRC_NAME TEST_LIBRARIES BUILD_ONLY)

	get_filename_component(DIR_NAME ${CMAKE_CURRENT_BINARY_DIR} NAME_WE)

	add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${SRC_NAME}.cpp)
	target_link_libraries(${TEST_NAME} ${TEST_LIBRARIES})
	target_link_libraries(${TEST_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	target_link_libraries(${TEST_NAME} ${EAGINE_THIRD_PARTY_LIBRARIES})

	add_custom_target(build-${DIR_NAME}-${TEST_NAME} DEPENDS ${TEST_NAME})

	add_dependencies(${DIR_NAME}-tests build-${DIR_NAME}-${TEST_NAME})

	add_test(
		build-test-${DIR_NAME}-${TEST_NAME}
		"${CMAKE_COMMAND}"
		--build ${CMAKE_BINARY_DIR}
		--target ${TEST_NAME}
	)

	if(NOT BUILD_ONLY)
		add_test(exec-test-${DIR_NAME}-${TEST_NAME} ${TEST_NAME})
		set_tests_properties(
			exec-test-${DIR_NAME}-${TEST_NAME}
			PROPERTIES DEPENDS
			build-test-${DIR_NAME}-${TEST_NAME}
		)
	endif()
endmacro()

function(eagine_build_test TEST_NAME)
	add_eagine_test("${TEST_NAME}" "${TEST_NAME}" "${ARGN}" TRUE)
endfunction()

function(eagine_exec_test TEST_NAME)
	add_eagine_test("${TEST_NAME}" "${TEST_NAME}" "${ARGN}" FALSE)
endfunction()

function(eagine_exec_test_sse TEST_NAME)
	add_eagine_test("${TEST_NAME}-sse" "${TEST_NAME}" "${ARGN}" FALSE)
	set_target_properties(
		"${TEST_NAME}-sse"
		PROPERTIES COMPILE_FLAGS
		"-DEAGINE_USE_SSE=1"
	)
	set_target_properties(
		"${TEST_NAME}-sse"
		PROPERTIES COMPILE_FLAGS
		"-march=native"
	)
endfunction()

function(eagine_exec_test_nosse TEST_NAME)
	add_eagine_test("${TEST_NAME}-nosse" "${TEST_NAME}" "${ARGN}" FALSE)
	set_target_properties(
		"${TEST_NAME}-nosse"
		PROPERTIES COMPILE_FLAGS
		"-DEAGINE_USE_SSE=0"
	)
endfunction()

function(eagine_test_dir)
	get_filename_component(DIR_NAME ${CMAKE_CURRENT_BINARY_DIR} NAME_WE)
	add_custom_target(${DIR_NAME}-tests)
endfunction()

