include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES "cobalt;process")
FetchContent_Declare(
  boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.90.0/boost-1.90.0-cmake.7z
)
FetchContent_MakeAvailable(boost)
