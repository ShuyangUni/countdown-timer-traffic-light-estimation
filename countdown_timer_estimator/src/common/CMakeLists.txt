add_library(common_data_loader SHARED "")
add_library(common::data_loader ALIAS common_data_loader)
target_sources(common_data_loader PUBLIC 
  data_loader.cc
  enum_transformer.cc
)
target_include_directories(common_data_loader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)