#include "buildxx.hpp"

void buildxx::build(build_ctx& ctx) {
  path header = HEADER;
  auto& build_exe = ctx.add<executable>("build_cc")
                        .file(ctx.build_script())
                        .std(23)
                        .link(BUILDXX_STATIC)
                        .link(BOOST_COBALT)
                        .link(BOOST_FILESYSTEM)
                        .link(BOOST_PROCESS)
                        .link(SPDLOG)
                        .link(FMT)
                        .include(header.parent_path())
                        .build();

  vector<string> argv(ctx.argv(), ctx.argv() + ctx.argc());

  ctx.build_step().depends_on(build_exe.run_step().flags(argv));
}
