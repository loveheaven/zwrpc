cmake_minimum_required(VERSION 3.1)
project(zwrpc)
set (CMAKE_CXX_STANDARD 11)

######################
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()
 
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS rec.proto)


######################
add_library(${PROJECT_NAME}  SHARED
EventDispatcher.cpp 
util.cpp
logging.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
/usr/local/include/
)
target_link_directories(${PROJECT_NAME} PRIVATE
/usr/local/lib
)
target_link_libraries(${PROJECT_NAME} 
libspdlog.a
fmt
gflags
)


###################################
add_executable(test 
main.cpp
${PROTO_SRCS} ${PROTO_HDRS}
)
target_include_directories(test PRIVATE
/usr/local/include/
)
target_link_directories(test PRIVATE
/usr/local/lib
)
target_link_libraries(test 
${PROJECT_NAME}
${PROTOBUF_LIBRARIES}
)
