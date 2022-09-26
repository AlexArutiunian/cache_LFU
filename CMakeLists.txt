cmake_minimum_required(VERSION 3.5)

project(lfu)

add_executable(lfu lfu.cpp lfu.hpp)

set_target_properties(
	lfu PROPERTIES
	CXX_STANDART 11
	CXX_STANDART_REQUIRED ON
)	
