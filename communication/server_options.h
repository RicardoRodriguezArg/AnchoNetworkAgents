#ifndef __AGENTS_MIDDLEWARE_SERVER_OPTIONS_H_
#define __AGENTS_MIDDLEWARE_SERVER_OPTIONS_H_
#include <algorithm>

#include "common/commons.h"
#include "eth_layer/udp_server.h"
#include "message_handler/message_handler.h"
#include "utils/utils.h"
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
