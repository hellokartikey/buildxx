add_executable(buildxx main.cpp)

target_sources(buildxx
PRIVATE
  cli.cpp

  ctx.cpp

  step.cpp

  target.cpp
  cmd.cpp
  exe.cpp

  tc.cpp
  tc_unix.cpp
)

target_link_libraries(buildxx
PRIVATE
  Boost::process
  CLI11::CLI11
  spdlog::spdlog
)
