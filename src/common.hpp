#ifndef HK_BUILDXX_COMMON_HPP
#define HK_BUILDXX_COMMON_HPP

#include <memory>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

namespace asio = boost::asio;
namespace fs = boost::filesystem;

namespace proc = boost::process;
namespace env = boost::process::environment;

template <class T> using ptr = std::shared_ptr<T>;

using namespace std::literals;

#endif
