#include "buildxx/buildxx.hpp"

#include <fstream>

#include <archive.h>
#include <archive_entry.h>
#include <spdlog/spdlog.h>

#ifdef BUILDXX_STATIC

const char buildxx_a[] = {
#embed BUNDLE
};

const char headers_tar[]{
#embed HEADERS
};

void extract_library(const buildxx::path& out) {
  buildxx::fs::create_directories(out.parent_path());
  std::ofstream file(out, std::ofstream::binary);
  file.write(buildxx_a, sizeof(buildxx_a));
}

#define AR_ERROR(ar, ret)                                                      \
  if ((ret) != ARCHIVE_OK)                                                     \
  throw error(fmt::format("libarchive: {}", archive_error_string((ar))))

void extract_headers(const buildxx::path& out) {
  using namespace buildxx;
  fs::create_directories(out);

  // 1. open archive
  auto ar = archive_read_new();
  archive_read_support_format_tar(ar);
  auto ret = archive_read_open_memory(ar, headers_tar, sizeof(headers_tar));
  AR_ERROR(ar, ret);

  while (true) {
    // 2. loop over files
    struct archive_entry* entry{};
    auto ret = archive_read_next_header(ar, &entry);
    if (ret == ARCHIVE_EOF)
      break;
    AR_ERROR(ar, ret);

    // 3. get filename and size
    auto pathname = archive_entry_pathname(entry);
    auto size = archive_entry_size(entry);
    if (size == 0)
      continue;

    // 4. read file content
    std::string buff;
    buff.resize(size);
    auto read_data = archive_read_data(ar, buff.data(), buff.capacity());

    std::ofstream file(out / pathname);
    file << buff;
  }

  archive_free(ar);
}

#endif

void buildxx::buildxx() {
#ifdef BUILDXX_STATIC
  path library_path = ctx.tmp() / path(BUNDLE).filename();
  path include_path = ctx.tmp() / "include" / "buildxx";

  extract_library(library_path);
  extract_headers(include_path);
#endif

  auto& build_exe = build()
                        .add<executable>("buildxx")
                        .file(build().build_script())
                        .std(23)
#ifdef BUILDXX_STATIC
                        .link(library_path)
                        .include(include_path.parent_path())
#else
                        .ld_flag("-lbuildxx")
#endif
                        .out_file(build().tmp() / "buildxx")
                        .install();

  vector<string> argv(cli().argv(), cli().argv() + cli().argc());
  build().build_step().depends_on(build_exe.run_step().flags(argv));
}
