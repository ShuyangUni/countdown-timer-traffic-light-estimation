cmake_minimum_required(VERSION 3.13.0)
project(countdown_timer_traffic_light)

option(USE_OPENMP "option for openmp" OFF)
if (USE_OPENMP)
    message("Use OpenMP.")
    add_definitions(-DUSE_OPENMP)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Do not specify CMAKE_BUILD_TYPE, set Release as default.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -O0 -Wall -g -pg -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -fPIC")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Eigen3 REQUIRED)
if(USE_OPENMP)
    find_package(OpenMP REQUIRED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${EIGEN3_INCLUDE_DIRS}
)

add_subdirectory(3rdparty/yaml-cpp)
# add_subdirectory(proto)
add_subdirectory(src)
add_subdirectory(apps)