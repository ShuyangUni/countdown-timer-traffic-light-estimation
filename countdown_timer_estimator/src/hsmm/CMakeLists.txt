add_library(cttl_hsmm SHARED "")
add_library(cttl::hsmm ALIAS cttl_hsmm)
target_sources(cttl_hsmm PUBLIC
  hsmm_worker.cc 
  hsmm_parameter.cc
)
target_include_directories(cttl_hsmm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)