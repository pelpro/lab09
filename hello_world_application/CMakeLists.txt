cmake_minimum_required(VERSION 3.8)
project(hello)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_world hello_world.cpp)

include_directories(${CMAKE_SOURCE_DIR}/formatter_ex_lib)

target_link_libraries(hello_world 
	${CMAKE_SOURCE_DIR}/formatter_ex_lib/libformatter_ex.a
	${CMAKE_SOURCE_DIR}/formatter_lib/libformatter.a
	)
