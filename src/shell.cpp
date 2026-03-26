#include "shell.hpp"

#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

namespace buildxx {
shell& shell::bin(const char* exe) { return bin(string(exe)); }

shell& shell::bin(const string& exe) { return bin(env::find_executable(exe)); }

shell& shell::bin(const path& exe) {
  m_exe = exe;
  m_nop = false;
  return *this;
}

shell& shell::flag(const string& arg) {
  m_args.push_back(arg);
  return *this;
}

shell& shell::flags(const vector<string>& args) {
  m_args.append_range(args);
  return *this;
}

shell& shell::env(const string& key, const string& value) {
  m_env[key] = value;
  return *this;
}

shell& shell::message(const string& msg) {
  m_msg = msg;
  return *this;
}

shell& shell::depends_on(shell& other) {
  m_depends.push_back(&other);
  return *this;
}

task<int> shell::exec() {
  if (is_done()) {
    co_return rc();
  }

  vector<task<int>> depends;

  for (auto* dep : m_depends) {
    depends.push_back(dep->exec());
  }

  co_await co::join(depends);

  if (is_nop()) {
    co_return 0;
  }

  auto env_map = m_env;
  for (const auto& kv : env::current()) {
    env_map[kv.key()] = kv.value();
  }

  if (not m_msg.empty()) {
    spdlog::info(m_msg);
  }

  fmt::print("{} {}\n", m_exe.string(), fmt::join(m_args, " "));

  if (auto p = out_file().parent_path(); not p.empty() and not fs::exists(p)) {
    if (not fs::create_directories(p)) {
      throw error(fmt::format("unable to create directory: {}", p.string()));
    }
  }

  proc::process handle(co_await co::this_coro::executor, m_exe, m_args,
                       proc::process_environment(env_map));

  m_rc = co_await handle.async_wait();

  if (not is_ok()) {
    throw error(
        fmt::format("{} returned with exit code {}", m_exe.string(), m_rc));
  }

  co_return m_rc;
}

int shell::rc() const { return m_rc; }

bool shell::is_done() const { return rc() != RC_NULL; }

bool shell::is_ok() const { return rc() == RC_OK; }

bool shell::is_phony() const { return m_is_phony; }

bool shell::is_nop() const { return m_nop; }

const vector<path>& shell::in_files() const { return m_in_files; }

shell& shell::in_file(path file) {
  m_args.push_back(file.string());
  m_in_files.push_back(file);
  return *this;
}

shell& shell::in_files(const vector<path>& files) {
  for (auto& file : files) {
    in_file(file);
  }

  return *this;
}

const path& shell::out_file() const { return m_out_file; }

shell& shell::out_file(path file) {
  m_args.push_back(file.string());
  m_out_file = file;
  m_is_phony = false;
  return *this;
}
} // namespace buildxx
