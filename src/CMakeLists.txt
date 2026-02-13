add_library(buildxx_static)
set_target_properties(buildxx_static PROPERTIES OUTPUT_NAME buildxx)

target_sources(buildxx_static
PRIVATE
  main.cpp

  cli.cpp
  build_ctx.cpp
  step.cpp

  target.cpp
  phony.cpp
  command.cpp
  executable.cpp
  library.cpp

  toolchain.cpp
  unix_toolchain.cpp
)

target_link_libraries(buildxx_static
PRIVATE
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)

add_executable(buildxx build.cpp)

target_link_libraries(buildxx PRIVATE buildxx_static)
