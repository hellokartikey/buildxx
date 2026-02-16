add_library(libbxx SHARED)
set_target_properties(libbxx PROPERTIES OUTPUT_NAME bxx)

target_sources(libbxx
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

target_link_libraries(libbxx
PUBLIC
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)

add_executable(bxx main.cpp)
target_link_libraries(bxx PRIVATE libbxx dylib)

install(TARGETS bxx libbxx)
