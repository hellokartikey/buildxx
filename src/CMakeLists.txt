add_executable(buildxx main.cpp)

target_link_libraries(buildxx PRIVATE Boost::process CLI11::CLI11)
