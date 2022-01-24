#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMONS_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMONS_H_
#include "interface/message_interface_idl.pb.h"

namespace namespace agents {
namespace middleware {
struct DataDecoder {

  ::agent_interface_CommandWithArguments
  DecodeToCommand(const std::string &raw_data_input) {
    ::agent_interface_CommandWithArguments command_with_argument{};
    std::memcpy(buffer_, raw_message.c_str(), raw_message.size());
    const auto &istream = pb_istream_from_buffer(buffer_, raw_message.size());
    pb_decode(&istream, pb_field_, &command_with_argument);
    return command_with_argument;
  }

  ::_agent_interface_Event DecodeToEvent(const std::string &raw_data_input) {
    ::_agent_interface_Event event{};
    std::memcpy(buffer_, raw_message.c_str(), raw_message.size());
    const auto &istream = pb_istream_from_buffer(buffer_, raw_message.size());
    agent_interface_CommandWithArguments command_with_argument;
    pb_decode(&istream, pb_field_, &command_with_argument);
    return event;
  }

  std::uint8_t *buffer_;
  const pb_field_t *pb_field_;
};
} // namespace middleware
} // namespace agents
#endif