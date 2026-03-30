add_library(libbuildxx STATIC)
set_target_properties(libbuildxx PROPERTIES OUTPUT_NAME buildxx)
target_compile_definitions(libbuildxx PUBLIC BOOST_PROCESS_USE_STD_FS)

target_sources(libbuildxx
PRIVATE
  build_ctx.cpp
  executable.cpp
  library.cpp
  main.cpp
  shell.cpp
  toolchain.cpp
  target.cpp
  utils.cpp

PUBLIC FILE_SET HEADERS FILES
  buildxx/build_ctx.hpp
  buildxx/buildxx.hpp
  buildxx/entry.hpp
  buildxx/executable.hpp
  buildxx/library.hpp
  buildxx/option.hpp
  buildxx/shell.hpp
  buildxx/target.hpp
  buildxx/task.hpp
  buildxx/toolchain.hpp
  buildxx/types.hpp
  buildxx/utils.hpp
)

target_link_libraries(libbuildxx
PRIVATE
  Boost::cobalt
  Boost::process
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
  "-static"
)

add_custom_command(
OUTPUT headers.tar
COMMENT "Archiving headers"
COMMAND ${TAR} -cf headers.tar
  --transform='s|.*buildxx/||'
  ${CMAKE_CURRENT_SOURCE_DIR}/buildxx/
)

bundle_static_library(libbuildxx buildxx_bundle)
add_executable(buildxx buildxx.cpp)
target_compile_definitions(buildxx
PRIVATE
  BUNDLE="$<TARGET_FILE:buildxx_bundle>"
  HEADERS="${CMAKE_CURRENT_BINARY_DIR}/headers.tar"
)
target_sources(buildxx PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/headers.tar")
target_link_libraries(buildxx PRIVATE libbuildxx archive_static "-static")

install(TARGETS buildxx libbuildxx FILE_SET HEADERS)
