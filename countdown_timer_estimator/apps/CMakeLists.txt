## demo_single_sequence
add_executable(demo_single_sequence
  demo_single_sequence.cc
)
add_dependencies(demo_single_sequence
  cttl::data_loader
  cttl::hsmm  
)
target_include_directories(demo_single_sequence PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
target_link_libraries(demo_single_sequence
  cttl::data_loader
  cttl::hsmm
)