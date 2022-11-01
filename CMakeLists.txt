cmake_minimum_required(VERSION 3.5)

project(lfu)



add_executable(lfu lfu.cpp)

set_target_properties(
	lfu PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

add_executable(test_ideal tests/test_ideal.cpp)

set_target_properties(
	test_ideal PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

add_executable(ideal ideal.cpp)

set_target_properties(
	ideal PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

add_executable(lfu_test tests/lfu_test.cpp)

set_target_properties(
	lfu_test PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

