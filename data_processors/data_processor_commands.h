#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMANDS_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMANDS_H_

#include "interface/message_interface_idl.pb.h"

namespace agents {
namespace middleware {
struct CommandsProcessor {
  void Process(const std::string &raw_message) {
    if (!raw_message.empty()) {
      std::memcpy(buffer_, raw_message.c_str(), raw_message.size());
    }
  }
  std::uint8_t *buffer_;
};
} // namespace middleware
} // namespace agents
#endif