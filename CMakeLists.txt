cmake_minimum_required(VERSION 2.8)
project(luatinkerE)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

if(COMPILER_SUPPORTS_CXX14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
endif()

set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(lua-5.3.5)

include_directories(lua-5.3.5/src luatinkere tests)

link_directories( ${LIBRARY_OUTPUT_PATH})


aux_source_directory(luatinkere cur_src)
aux_source_directory(tests cur_src)


#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lua-5.3.5/src) #添加动态连接库的路径

message(STATUS {${cur_src}})
add_executable(test_runner ${cur_src})

target_link_libraries(test_runner lua dl)