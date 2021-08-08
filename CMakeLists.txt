cmake_minimum_required(VERSION 3.1)
project(zwrpc)
set (CMAKE_CXX_STANDARD 11)


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
add_executable(test main.cpp)
target_include_directories(test PRIVATE
/usr/local/include/
)
target_link_directories(test PRIVATE
/usr/local/lib
)
target_link_libraries(test 
${PROJECT_NAME}
)
