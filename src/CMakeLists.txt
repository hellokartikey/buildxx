add_executable(buildxx main.cpp)

target_sources(buildxx
PRIVATE
  cli.cpp
  build_ctx.cpp
  step.cpp

  target.cpp
  command.cpp
  executable.cpp

  toolchain.cpp
  unix_toolchain.cpp
)

target_link_libraries(buildxx
PRIVATE
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)
