target_sources(libbuildxx
PRIVATE
  build_ctx.cpp
  executable.cpp
  files.cpp
  library.cpp
  main.cpp
  shell.cpp
  toolchain.cpp
  target.cpp
  utils.cpp
)

target_link_libraries(libbuildxx
PRIVATE
  Boost::cobalt
  Boost::process
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
)

target_link_libraries(buildxx PRIVATE libbuildxx fmt::fmt)

if(BUILDXX_STATIC)
  target_link_libraries(buildxx PRIVATE archive_static "-static")

  target_sources(libbuildxx
  PRIVATE
    $<TARGET_OBJECTS:Boost::cobalt>
    $<TARGET_OBJECTS:Boost::process>
    $<TARGET_OBJECTS:fmt::fmt>
    $<TARGET_OBJECTS:spdlog::spdlog>
  )

  target_compile_definitions(buildxx
  PRIVATE
    BUILDXX_STATIC
    BUNDLE="$<TARGET_FILE:libbuildxx>"
    HEADERS="${CMAKE_CURRENT_BINARY_DIR}/headers.tar"
  )
endif(BUILDXX_STATIC)

