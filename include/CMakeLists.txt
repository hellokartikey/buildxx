target_sources(libbuildxx
PUBLIC FILE_SET HEADERS FILES
  buildxx/async_rc.hpp
  buildxx/build_ctx.hpp
  buildxx/buildxx.hpp
  buildxx/entry.hpp
  buildxx/executable.hpp
  buildxx/files.hpp
  buildxx/library.hpp
  buildxx/option.hpp
  buildxx/shell.hpp
  buildxx/target.hpp
  buildxx/toolchain.hpp
  buildxx/types.hpp
  buildxx/utils.hpp
)

if(BUILDXX_STATIC)
  add_custom_command(
    OUTPUT headers.tar
    DEPENDS libbuildxx
    COMMENT "Archiving headers"
    COMMAND ${TAR} -cf headers.tar
      --transform='s|.*buildxx/||'
      ${CMAKE_CURRENT_SOURCE_DIR}/buildxx/
  )
  target_sources(buildxx PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/headers.tar")
endif(BUILDXX_STATIC)
