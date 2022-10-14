cmake_minimum_required(VERSION 3.5)

project(lfu_test)

add_executable(lfu_test lfu_test.cpp ../headers/lfu1.hpp ../headers/lfuN.hpp ../headers/lfuNLOGN.hpp random_test.hpp)

set_target_properties(
	lfu_test PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)