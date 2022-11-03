cmake_minimum_required(VERSION 3.22)

project(lfu)

list(APPEND bin lfu test_ideal ideal lfu_test test_lfu_vs_ideal lfu_assert_test ideal_assert_test)
list(APPEND cpp lfu.cpp tests/random_tests/test_ideal.cpp 
ideal.cpp tests/random_tests/lfu_test.cpp 
tests/random_tests/test_lfu_vs_ideal.cpp tests/assert_tests/lfu_assert_test.cpp
tests/assert_tests/ideal_assert_test.cpp)

foreach(build IN ZIP_LISTS bin cpp)
	add_executable(${build_0} ${build_1})

    set_target_properties(
	${build_0} PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

endforeach()
