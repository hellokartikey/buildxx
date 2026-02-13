add_library(buildxx-lib)

target_sources(buildxx-lib
PRIVATE
  main.cpp

  cli.cpp
  build_ctx.cpp
  step.cpp

  target.cpp
  phony.cpp
  command.cpp
  executable.cpp

  toolchain.cpp
  unix_toolchain.cpp
)

target_link_libraries(buildxx-lib
PRIVATE
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)

add_executable(buildxx build.cpp)

target_link_libraries(buildxx PRIVATE buildxx-lib)
