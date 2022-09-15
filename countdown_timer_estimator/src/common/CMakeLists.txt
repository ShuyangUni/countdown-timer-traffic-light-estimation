add_library(cttl_data_loader SHARED "")
add_library(cttl::data_loader ALIAS cttl_data_loader)
target_sources(cttl_data_loader PUBLIC 
  data_loader.cc
  enum_transformer.cc
)
target_include_directories(cttl_data_loader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)