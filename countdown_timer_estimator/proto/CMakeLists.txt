find_package(Protobuf REQUIRED)
# FILE(GLOB protofiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
# message(STATUS "proto files:")
# message("    ${protofiles}")
# PROTOBUF_GENERATE_CPP(PROTOSRCS PROTOHDRS ${protofiles})
# message(STATUS "output src files")
# message("    ${PROTOSRCS}")

add_library(cttl_proto SHARED "")
add_library(cttl::proto ALIAS cttl_proto)
target_sources(cttl_proto 
    PUBLIC
    # ${PROTOHDRS}
    # ${PROTOSRCS}
    hsmm_parameter.pb.cc
)
target_include_directories(cttl_proto
    PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROTOBUF_INCLUDE_DIRS}
)
target_link_libraries(cttl_proto 
    ${PROTOBUF_LIBRARIES}
)