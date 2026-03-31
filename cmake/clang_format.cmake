find_program(CLANGFORMAT REQUIRED NAMES clang-format)
file(GLOB_RECURSE ALL_SRC src/*.hpp src/*.cpp)
add_custom_target(clang-format COMMAND ${CLANGFORMAT} -i -style=file ${ALL_SRC})
