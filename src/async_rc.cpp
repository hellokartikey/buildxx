#include "buildxx/async_rc.hpp"

namespace buildxx {
async_rc rc_promise::get_return_object() {
  return {async_rc::from_promise(*this)};
}

std::suspend_always rc_promise::initial_suspend() noexcept { return {}; }

std::suspend_always rc_promise::final_suspend() noexcept { return {}; }

void rc_promise::return_value(int value) { m_value = value; }

void rc_promise::return_value(std::future<int> value) {
  m_value = std::move(value);
}

void rc_promise::unhandled_exception() { throw; }

rc_promise::variant& rc_promise::value() { return m_value; }

const rc_promise::variant& rc_promise::value() const { return m_value; }

bool async_rc::await_ready() const noexcept {
  auto& value = promise().value();
  if (std::holds_alternative<std::monostate>(value)) {
    return false;
  } else {
    return true;
  }
}

void async_rc::await_suspend(std::coroutine_handle<> handle) const noexcept {
  handle.resume();
}

void async_rc::await_resume() const noexcept {}
} // namespace buildxx
