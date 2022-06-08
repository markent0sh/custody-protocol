project(publisher-node)

include(${CMAKE_SOURCE_DIR}/cmake/grpc_generator.cmake)

set(PROTO_LIB publisher_pt_lib)

generate_grpc_lib(
  ${CMAKE_CURRENT_LIST_DIR}/../api
  publisher
  ${PROTO_LIB}
)

list(APPEND PUBLISHER_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/server/node_server.cpp
)

list(APPEND PUBLISHER_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/server
)

add_executable(${PROJECT_NAME} ${PUBLISHER_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLISHER_INCLUDES})

target_link_libraries(${PROJECT_NAME} ${PROTO_LIB})

add_executable(testclient testclient.cc)

target_include_directories(testclient PUBLIC ${PUBLISHER_INCLUDES})

target_link_libraries(testclient ${PROTO_LIB})
