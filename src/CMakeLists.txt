add_library(buildxx_static)

target_sources(buildxx_static
PRIVATE
  build_ctx.cpp
  shell.cpp
)

target_link_libraries(buildxx_static
PUBLIC
  Boost::cobalt
  Boost::process
  spdlog::spdlog
)

add_executable(buildxx main.cpp)
target_link_libraries(buildxx PRIVATE buildxx_static CLI11::CLI11)

install(TARGETS buildxx)
