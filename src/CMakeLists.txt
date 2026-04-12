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

add_custom_command(
OUTPUT headers.tar
DEPENDS libbuildxx
COMMENT "Archiving headers"
COMMAND ${TAR} -cf headers.tar
  --transform='s|.*buildxx/||'
  ${CMAKE_CURRENT_SOURCE_DIR}/buildxx/
)

target_compile_definitions(buildxx
PRIVATE
  BUNDLE="$<TARGET_FILE:buildxx_bundle>"
  HEADERS="${CMAKE_CURRENT_BINARY_DIR}/headers.tar"
)
target_sources(buildxx PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/headers.tar")
target_link_libraries(buildxx PRIVATE libbuildxx)

if(BUILDXX_STATIC)
  target_link_libraries(buildxx PRIVATE archive_static "-static")
  target_compile_definitions(buildxx PRIVATE BUILDXX_STATIC)
else(BUILDXX_STATIC)
  target_link_libraries(buildxx PRIVATE LibArchive::LibArchive)
endif(BUILDXX_STATIC)
