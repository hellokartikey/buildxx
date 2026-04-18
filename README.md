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
└── build.cpp
```

The `build.cpp` describes the build graph.

```C++
#include <buildxx/buildxx.hpp>

void buildxx::buildxx() {
  auto src = build().dir("src");

  auto foo = build()
    .add<library>("foo")
    .shared(true)
    .file(src / "foo.cpp");

  auto main = build()
    .add<executable>("main")
    .std(23)
    .file(src / "main.cpp")
    .link(foo)
    .install();
}
```

Build the project using simple command,

```
buildxx
```

Alternatively, provide a custom build script,

```
buildxx build.cc
```

## Build

Currently buildxx is configured to build a fully static binary with all the
dependencies.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
