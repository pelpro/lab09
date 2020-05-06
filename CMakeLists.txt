cmake_minimum_required(VERSION 3.4)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
    SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)


project(print)
hunter_add_package(GTest)
hunter_add_package(nlohmann_json)

find_package(GTest CONFIG REQUIRED)
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
set(PRINT_VERSION
  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_MAJOR 1)

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
  add_subdirectory(banking)
  include_directories(banking)
  enable_testing()
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check ${PROJECT_NAME} GTest::gtest_main GTest::gmock_main banking)
  add_test(NAME check COMMAND check)
endif()

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)
target_link_libraries(demo print)
install(TARGETS demo RUNTIME DESTINATION bin)

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} print)
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    )
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

include(CPackConfig.cmake)
