#ifndef BUILDXX_ASYNC_RC_HPP
#define BUILDXX_ASYNC_RC_HPP

#include <coroutine>
#include <future>
#include <variant>

#include "types.hpp"

namespace buildxx {
class async_rc;

class rc_promise {
public:
  using variant = std::variant<std::monostate, int, std::future<int>>;

  async_rc get_return_object();

  std::suspend_always initial_suspend() noexcept;
  std::suspend_always final_suspend() noexcept;

  void return_value(int value);
  void return_value(std::future<int> value);

  void unhandled_exception();

  variant& value();
  const variant& value() const;

private:
  variant m_value;
};

class async_rc : public std::coroutine_handle<rc_promise> {
public:
  using promise_type = rc_promise;

  bool await_ready() const noexcept;
  void await_suspend(std::coroutine_handle<> handle) const noexcept;
  void await_resume() const noexcept;
};
}

#endif
