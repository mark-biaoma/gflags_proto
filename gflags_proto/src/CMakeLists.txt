include_directories(../include)
include_directories(../include/base)

aux_source_directory(. source_list)
aux_source_directory(./base source_list_base)

# 添加 gflags 包的查找路径
find_package(gflags REQUIRED)

# 查找 protobuf
find_package(Protobuf REQUIRED)
if (PROTOBUF_FOUND)
    message("protobuf found")
else ()
    message(FATAL_ERROR "Cannot find Protobuf")
endif ()

# 编译 proto 为 .cpp 和 .h
set(PROTO_FILES ../proto/test_proto.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
message("PROTO_SRCS = ${PROTO_SRCS}")
message("PROTO_HDRS = ${PROTO_HDRS}")

add_executable(${PROJECT_NAME} main.cc ${source_list} 
                    ${source_list_base}
                    ${PROTO_SRCS} 
                    ${PROTO_HDRS})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} gflags ${PROTOBUF_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)