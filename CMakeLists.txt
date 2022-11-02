cmake_minimum_required(VERSION 3.5)

project(lfu)

list(APPEND bin lfu test_ideal ideal lfu_test test_lfu_vs_ideal)
list(APPEND cpp lfu.cpp tests/test_ideal.cpp ideal.cpp tests/lfu_test.cpp tests/test_lfu_vs_ideal.cpp)

foreach(build IN ZIP_LISTS bin cpp)
	add_executable(${build_0} ${build_1})

    set_target_properties(
	${build_0} PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

endforeach()
