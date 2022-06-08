cmake_minimum_required(VERSION 3.2)

include(FetchContent)

FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.46.3
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)

if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

function(generate_grpc_lib PROTO_PATH PROTO_NAME OUT_NAME)
  set(FULL_PROTO_PATH "${PROTO_PATH}/${PROTO_NAME}.proto")

  get_filename_component(PROTO_GEN ${FULL_PROTO_PATH} ABSOLUTE)
  get_filename_component(PROTO_GEN_PATH ${PROTO_GEN} PATH)

  list(APPEND GRPC_GENERATED_SOURCES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.pb.h"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.h"
  )

  add_custom_command(
      OUTPUT ${GRPC_GENERATED_SOURCES}
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${PROTO_GEN_PATH}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${PROTO_GEN}"
      DEPENDS "${PROTO_GEN}"
  )

  include_directories(${CMAKE_CURRENT_BINARY_DIR})

  add_library(${OUT_NAME} ${GRPC_GENERATED_SOURCES})
  target_include_directories(${OUT_NAME} PUBLIC ${GRPC_GENERATED_SOURCES})
  target_link_libraries(${OUT_NAME} ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
endfunction()
