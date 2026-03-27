add_library(buildxx_static)

target_sources(buildxx_static
PRIVATE
  build_ctx.cpp
  shell.cpp

  toolchain.cpp
  target.cpp
  executable.cpp
  library.cpp

  build_main.cpp
)

target_link_libraries(buildxx_static
PUBLIC
  Boost::cobalt
  Boost::filesystem
  Boost::process
  spdlog::spdlog
)

add_executable(buildxx main.cpp)
target_compile_definitions(buildxx PRIVATE
  BUILDXX_STATIC="$<TARGET_FILE:buildxx_static>"
  BOOST_COBALT="$<TARGET_FILE:Boost::cobalt>"
  BOOST_FILESYSTEM="$<TARGET_FILE:Boost::filesystem>"
  BOOST_PROCESS="$<TARGET_FILE:Boost::process>"
  SPDLOG="$<TARGET_FILE:spdlog::spdlog>"
  FMT="$<TARGET_FILE:fmt::fmt>"
)
target_link_libraries(buildxx PRIVATE buildxx_static CLI11::CLI11)

install(TARGETS buildxx)
