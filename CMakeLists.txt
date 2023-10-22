message("[Beginner][CMake] Welcom to CMake")
cmake_minimum_required(VERSION 3.5)
project(Beginner)

message("[Beginner][CMake] Set the version of this project")
set(Beginner_VERSION_MAJOR 1)
set(Beginner_VERSION_MINOR 0)

message("[Beginner][CMake] Set the compilation mode of this project")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

message("[Beginner][CMake] Begin to configure the head file")
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/include/config.h"
)

#find_package(SDL REQUIRED)

file(GLOB_RECURSE PROJECT_SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(Beginner ${PROJECT_SRC_LIST})

set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_BINARY_DIR}/include/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/Compress/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/Foundation/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/Layer/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/Object/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/SDL2/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/SDL2/mixer/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/State/)
set(PROJECT_INCLUDE_LIST ${PROJECT_INCLUDE_LIST} ${PROJECT_SOURCE_DIR}/include/TinyXml/)
target_include_directories(Beginner PRIVATE "${PROJECT_INCLUDE_LIST}")

file(GLOB PROJECT_LIB_LIST lib/SDL2/*.lib lib/SDL2/mixer/*.lib lib/SDL2/*.dll lib/SDL2/mixer/*.dll lib/zlib/*.dll)
target_link_libraries(Beginner PRIVATE "${PROJECT_LIB_LIST}")
#target_link_libraries(Beginner PRIVATE SDL)