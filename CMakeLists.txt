cmake_minimum_required(VERSION 3.5)

project(lfu)

add_executable(lfu lfu.cpp headers/lfu1.hpp headers/lfuN.hpp headers/lfuNLOGN.hpp)

set_target_properties(
	lfu PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)