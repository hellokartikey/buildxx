cmake_minimum_required(VERSION 4.0)

project(buildxx)

option(HK_CLANG_FORMAT "enable clang-format" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost REQUIRED COMPONENTS process)
find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)

if (HK_CLANG_FORMAT)
  find_program(CLANG_FORMAT REQUIRED NAMES clang-format)
  file(GLOB_RECURSE ALL_SRC src/*.hpp src/*.cpp)
  add_custom_target(
    clang-format
    COMMAND
      ${CLANG_FORMAT} -i -style=file ${ALL_SRC}
  )
endif()

add_subdirectory(src)
