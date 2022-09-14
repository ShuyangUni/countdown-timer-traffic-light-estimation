add_library(common_hsmm SHARED "")
add_library(common::hsmm ALIAS common_hsmm)
target_sources(common_hsmm PUBLIC
  hsmm_worker.cc 
  hsmm_parameter.cc
)
target_include_directories(common_hsmm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)