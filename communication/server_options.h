#ifndef __AGENTS_MIDDLEWARE_SERVER_OPTIONS_H_
#define __AGENTS_MIDDLEWARE_SERVER_OPTIONS_H_
#include <algorithm>

// x86
namespace agents {
  namespace middleware {
    namespace options {
      struct ServerConfiguration {
        std::uint16_t server_port_ = 9999U;
      }

    }; // namespace options
  }    // namespace middleware
} // namespace agents
