add_library(buildxx_lib SHARED)
set_target_properties(buildxx_lib PROPERTIES OUTPUT_NAME buildxx)

target_sources(buildxx_lib
PRIVATE
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

target_link_libraries(buildxx_lib
PUBLIC
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)

add_executable(buildxx main.cpp)
target_link_libraries(buildxx PRIVATE buildxx_lib dylib)
