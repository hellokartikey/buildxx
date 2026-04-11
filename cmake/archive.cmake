include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

set(ENABLE_ACL OFF)
set(ENABLE_BZip2 OFF)
set(ENABLE_CAT OFF)
set(ENABLE_CPIO OFF)
set(ENABLE_EXPAT OFF)
set(ENABLE_ICONV OFF)
set(ENABLE_LIBB2 OFF)
set(ENABLE_LIBXML2 OFF)
set(ENABLE_LZ4 OFF)
set(ENABLE_LZMA OFF)
set(ENABLE_MD OFF)
set(ENABLE_OPENSSL OFF)
set(ENABLE_TAR OFF)
set(ENABLE_UNZIP OFF)
set(ENABLE_WIN32_XMLLITE OFF)
set(ENABLE_XATTR OFF)
set(ENABLE_ZLIB OFF)
set(ENABLE_ZSTD OFF)

set(ENABLE_TEST OFF)
FetchContent_Declare(
  archive
  URL https://github.com/libarchive/libarchive/releases/download/v3.8.6/libarchive-3.8.6.tar.gz
  PATCH_COMMAND patch CMakeLists.txt ${CMAKE_SOURCE_DIR}/cmake/archive.patch
)
FetchContent_MakeAvailable(archive)
