# Buildxx

An attempt at a build system for C++ in C++ itself.

## Quick Start

Buildxx doesn't opine on any project structure. Here is a simple example.

```
.
├── src
│   ├── foo.cpp
│   ├── foo.hpp
│   └── main.cpp
├── build.cpp
```

The build script is a C++ file, which describes the build graph.

```C++
#include <buildxx/buildxx.hpp>

void buildxx::build(build_ctx& ctx) {
  auto src = ctx.dir("src");

  auto foo = ctx.add<library>("foo")
    .shared(true)
    .file(src / "foo.cpp");

  auto main = ctx.add<executable>("main")
    .std(23)
    .file(src / "main.cpp")
    .link(foo)
    .build();
}
```

## Build

Currently buildxx is built using CMake.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
