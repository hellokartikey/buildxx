#include <buildxx/buildxx.hpp>

#include <chrono>
#include <thread>

#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/cobalt/join.hpp>
#include <boost/cobalt/this_coro.hpp>
#include <boost/process.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

namespace buildxx {
namespace asio = boost::asio;
namespace co = boost::cobalt;
namespace proc = boost::process;
namespace env = proc::environment;

shell& shell::bin(const char* exe) { return bin(string(exe)); }

shell& shell::bin(const string& exe) { return bin(find_executable(exe)); }

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

int shell::exec(bool verbose) {
  // 1. acquire mutex
  auto _ = std::lock_guard(m_mutex);

  // 2. check if already exec
  if (m_rc != RC_NULL) {
    return m_rc;
  }

  // 3. await dependencies
  for (auto* dep : m_depends) {
    dep->exec(verbose);
  }

  // 4. return if nothing to do
  if (is_nop()) {
    return m_rc;
  }

  // 5. prepare environment
  map<env::key, env::value> env_map;
  for (const auto& kv : env::current()) {
    env_map[kv.key()] = kv.value();
  }

  for (const auto& [k, v] : m_env) {
    env_map[k] = v;
  }

  // 6. print message
  if (not m_msg.empty()) {
    spdlog::info(m_msg);
  }

  // 7. print command to execute
  if (verbose) {
    fmt::print("{} {}\n", m_exe.string(), fmt::join(m_args, " "));
  }

  // 8. create out_file() directory just in case
  if (auto p = out_file().parent_path(); not p.empty() and not fs::exists(p)) {
    if (not fs::create_directories(p)) {
      throw error(fmt::format("unable to create directory: {}", p.string()));
    }
  }

  // 9. create and await process
  proc::process handle(co::this_thread::get_executor(), m_exe, m_args,
                       proc::process_environment(env_map));

  // 10. wait for return code
  m_rc = handle.wait();

  if (not is_ok()) {
    throw error(
        fmt::format("{} returned with exit code {}", m_exe.string(), m_rc));
  }

  return m_rc;
}

int shell::rc() const { return m_rc; }

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
