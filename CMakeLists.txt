cmake_minimum_required(VERSION 4.0)
project(buildxx VERSION 0.2)
option(HK_CLANG_FORMAT "enable clang-format" ON)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_program(TAR tar REQUIRED)

include(cmake/bundle.cmake)
include(cmake/archive.cmake)
include(cmake/boost.cmake)
include(cmake/cli11.cmake)
include(cmake/fmt.cmake)
include(cmake/spdlog.cmake)

if (HK_CLANG_FORMAT)
  include(cmake/clang_format.cmake)
endif()

add_subdirectory(src)
