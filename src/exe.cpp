#include "exe.hpp"

#include <print>

#include "ctx.hpp"

namespace bxx {
exe::exe(private_tag, ptr<ctx> ctx, std::string name, fs::path entry)
    : target(private_tag{}, name)
    , m_ctx(ctx)
    , m_exe(m_ctx->bin() / exe::name()) {
  m_link = m_ctx->add_step(m_ctx->tc()->cxx())
               ->add_opt({"-o", m_exe.string()})
               ->add_opt(m_ctx->tc()->ld_opts())
               ->add_msg(std::format("Linking C++ executable {}",
                                     fs::relative(m_exe).string()));

  add_obj(entry);
}

ptr<exe> exe::create(ptr<ctx> ctx, std::string name, fs::path entry) {
  return std::make_shared<exe>(private_tag{}, ctx, std::move(name),
                               std::move(entry));
}

ptr<exe> exe::add_src(fs::path src) {
  add_obj(src);
  return get();
}

ptr<exe> exe::add_src(fs::path prefix, std::vector<std::string> files) {
  for (auto& file : files) {
    add_src(prefix / file);
  }

  return get();
}

ptr<target> exe::install() {
  target::install();
  m_link->install();
  return get();
}

void exe::add_obj(fs::path entry) {
  using namespace std::literals;

  auto src = m_ctx->dir() / entry;
  auto obj = m_ctx->cache() / entry;
  obj += ".o";

  // 1. create object folder if not exists
  if (!fs::exists(obj.parent_path())) {
    fs::create_directory(obj.parent_path());
  }

  // 2. compile object step
  auto step = m_ctx->add_step(m_ctx->tc()->cxx())
                  ->add_opt(m_ctx->tc()->cxx_opts())
                  ->add_opt("-c")
                  ->add_opt(src.string())
                  ->add_opt({"-o", obj.string()})
                  ->add_msg(std::format("Building C++ object {}",
                                        fs::relative(obj).string()));

  m_steps.push_back(step);

  // 3. linker step
  m_link->add_opt(obj.string())->depends_on(step);
}
} // namespace bxx
