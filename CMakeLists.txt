cmake_minimum_required(VERSION 4.0)
project(buildxx VERSION 0.2)

option(CLANG_FORMAT "enable clang-format" ON)
option(BUILDXX_STATIC "enable fully static binary" OFF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (BUILDXX_STATIC)
  find_program(TAR tar REQUIRED)

  include(cmake/archive.cmake)
  include(cmake/boost.cmake)
  include(cmake/cli11.cmake)
  include(cmake/fmt.cmake)
  include(cmake/spdlog.cmake)
else()
  find_package(Boost REQUIRED COMPONENTS Process Cobalt)
  find_package(CLI11 REQUIRED)
  find_package(fmt REQUIRED)
  find_package(spdlog REQUIRED)
endif()

if(CLANG_FORMAT)
  include(cmake/clang_format.cmake)
endif(CLANG_FORMAT)

if(BUILDXX_STATIC)
  add_library(libbuildxx STATIC)
  message("Fully static build")
else(BUILDXX_STATIC)
  add_library(libbuildxx SHARED)
endif(BUILDXX_STATIC)

set_target_properties(libbuildxx PROPERTIES OUTPUT_NAME buildxx)
target_compile_definitions(libbuildxx PUBLIC BOOST_PROCESS_USE_STD_FS)
add_executable(buildxx src/buildxx.cpp)

add_subdirectory(src)
add_subdirectory(include)

install(TARGETS buildxx libbuildxx FILE_SET HEADERS)
