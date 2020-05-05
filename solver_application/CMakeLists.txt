cmake_minimum_required(VERSION 3.8)
project(hello)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(equation equation.cpp)

include_directories(
	${CMAKE_SOURCE_DIR}/../formatter_ex_lib
	${CMAKE_SOURCE_DIR}/../solver_lib
	)

target_link_libraries(equation 
	${CMAKE_SOURCE_DIR}/../formatter_ex_lib/libformatter_ex.a
	${CMAKE_SOURCE_DIR}/../formatter_lib/libformatter.a
	${CMAKE_SOURCE_DIR}/../solver_lib/libsolver.a
	)
