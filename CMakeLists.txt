cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(print)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/formatter_lib 
		${CMAKE_SOURCE_DIR}/formatter_lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/formatter_ex_lib 
                ${CMAKE_SOURCE_DIR}/formatter_ex_lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/solver_lib
                ${CMAKE_SOURCE_DIR}/solver_lib)


target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

file(GLOB EXE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*application")
foreach(EXE_NAME ${EXE_SOURCES})
	add_subdirectory(${EXE_NAME} ${EXE_NAME})
endforeach(EXE_NAME ${EXE_SOURCES})

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check ${PROJECT_NAME} gtest_main)
  add_test(NAME check COMMAND check)
endif()
