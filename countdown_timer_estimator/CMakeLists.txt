cmake_minimum_required(VERSION 3.13.0)
project(countdown_timer_traffic_light)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wall -g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -pg")

find_package(Eigen3 REQUIRED)
find_package(OpenMP REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# message("------------------------------------------")
# message("${OpenMP_C_FLAGS}")
# message("${OpenMP_CXX_FLAGS}")
# message("${OpenMP_EXE_LINKER_FLAGS}")
# message("------------------------------------------")

add_subdirectory(src)
add_subdirectory(apps)