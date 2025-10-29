cmake_minimum_required(VERSION 3.25)

set(TOOLCHAIN_DIR /usr/)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/g++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gemm-rv)

file(GLOB_RECURSE SOURCES main.cpp src/naive.cpp src/optimized.cpp src/utils.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=rv64imafdcv -g -O2")
