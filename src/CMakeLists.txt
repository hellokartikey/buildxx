add_library(buildxx_static)
set_target_properties(buildxx_static PROPERTIES OUTPUT_NAME buildxx)

file(GLOB_RECURSE BUILDXX_HEADERS "buildxx/*.hpp")

target_sources(buildxx_static
PRIVATE
  build_ctx.cpp
  shell.cpp
  toolchain.cpp
  target.cpp
  executable.cpp
  library.cpp
  main.cpp

PUBLIC
  FILE_SET HEADERS FILES ${BUILDXX_HEADERS}
)

target_link_libraries(buildxx_static
PUBLIC
  Boost::cobalt
  Boost::filesystem
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)

add_executable(buildxx buildxx.cpp)
target_compile_definitions(buildxx PRIVATE
  BUILDXX_STATIC="$<TARGET_FILE:buildxx_static>"
  BOOST_COBALT="$<TARGET_FILE:Boost::cobalt>"
  BOOST_FILESYSTEM="$<TARGET_FILE:Boost::filesystem>"
  BOOST_PROCESS="$<TARGET_FILE:Boost::process>"
  SPDLOG="$<TARGET_FILE:spdlog::spdlog>"
  FMT="$<TARGET_FILE:fmt::fmt>"
)
target_link_libraries(buildxx PRIVATE buildxx_static)

install(TARGETS buildxx buildxx_static FILE_SET HEADERS)
