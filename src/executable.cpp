#include "executable.hpp"

#include <print>

#include "ctx.hpp"

namespace bxx {
executable::executable(private_tag,
                       std::shared_ptr<ctx> ctx,
                       std::string name,
                       fs::path entry)
    : target(private_tag{}, name)
    , m_ctx(ctx) {
  m_link = m_ctx->add_step(m_ctx->toolchain()->cxx())
               ->add_options(
                   {"-o",
                    (m_ctx->binary_directory() / executable::name()).string()});

  add_entry(entry);
}

std::shared_ptr<executable>
executable::create(std::shared_ptr<ctx> ctx, std::string name, fs::path entry) {
  return std::make_shared<executable>(private_tag{}, ctx, std::move(name),
                                      std::move(entry));
}

std::shared_ptr<executable> executable::add_src(fs::path src) {
  add_entry(src);
  return get();
}

std::shared_ptr<executable>
executable::add_src(fs::path prefix, std::vector<std::string> files) {
  for (auto& file : files) {
    add_src(prefix / file);
  }

  return get();
}

std::shared_ptr<target> executable::install() {
  target::install();
  m_link->install();
  return get();
}

void executable::add_entry(fs::path entry) {
  using namespace std::literals;

  auto src = m_ctx->current_directory() / entry;
  auto obj = m_ctx->cache_directory() / entry;
  obj += ".o";

  // 1. create object folder if not exists
  if (!fs::exists(obj.parent_path())) {
    fs::create_directory(obj.parent_path());
  }

  // 2. compile object step
  auto step = m_ctx->add_step(m_ctx->toolchain()->cxx())
                  ->add_option("-c")
                  ->add_option(src.string())
                  ->add_options({"-o", obj.string()});

  m_steps.push_back(step);

  // 3. linker step
  m_link->add_option(obj.string())->depends_on(step);
}
} // namespace bxx
