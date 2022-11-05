cmake_minimum_required(VERSION 3.16)

project(lfu)

set(dir tests/random_tests/ tests/assert_tests/)
set(main lfu ideal)
set(tests_random test_ideal lfu_test
test_lfu_vs_ideal)
set(tests_assert lfu_assert_test
ideal_assert_test)

foreach(bin ${main})
	add_executable(${bin} ${bin}.cpp)
	message(${bin})
	set_target_properties(
		${bin} PROPERTIES
		CXX_STANDART 20
		CXX_STANDART_REQUIRED ON
	)
endforeach()

foreach(bin ${tests_random})
	add_executable(${bin} tests/random_tests/${bin}.cpp)
	message(${bin})
	set_target_properties(
		${bin} PROPERTIES
		CXX_STANDART 20
		CXX_STANDART_REQUIRED ON
	)
endforeach()

foreach(bin ${tests_assert})
	add_executable(${bin} tests/assert_tests/${bin}.cpp)
	message(${bin})
	set_target_properties(
		${bin} PROPERTIES
		CXX_STANDART 20
		CXX_STANDART_REQUIRED ON
	)
endforeach()