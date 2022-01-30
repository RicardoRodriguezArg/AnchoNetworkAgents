#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMONS_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMONS_H_
#include "interface/message_interface_idl.pb.h"

namespace namespace agents {
  namespace middleware {

    static constexpr MAX_MESSAGE_COUNT{500U};

    struct DataDecoder {

      ::agent_interface_CommandWithArguments DecodeToCommand(
        const std::string& raw_data_input) {
        ::agent_interface_CommandWithArguments command_with_argument{};
        std::memcpy(buffer_, raw_message.c_str(), raw_message.size());
        const auto& istream =
          pb_istream_from_buffer(buffer_, raw_message.size());
        pb_decode(&istream, pb_field_, &command_with_argument);
        return command_with_argument;
      }

      std::string EncodeCommand(
        const ::agent_interface_CommandWithArguments& command_to_encode) {
        std::string result{};
        stream_ = ::pb_ostream_from_buffer(buffer_, MAX_MESSAGE_COUNT);
        if (pb_encode(&stream_, pb_field_, &command_to_encode)) {
          result.assign(
            reinterpret_cast<char*>(buffer_), stream_.bytes_written);
        }
        return result;
      }

      ::_agent_interface_Event DecodeToEvent(
        const std::string& raw_data_input) {
        ::_agent_interface_Event event{};
        std::memcpy(buffer_, raw_message.c_str(), raw_message.size());
        const auto& istream =
          pb_istream_from_buffer(buffer_, raw_message.size());
        agent_interface_CommandWithArguments command_with_argument;
        pb_decode(&istream, pb_field_, &command_with_argument);
        return event;
      }

      std::uint8_t buffer_[MAX_MESSAGE_COUNT];
      const pb_field_t* pb_field_;
      pb_ostream_t stream_;
    };
  } // namespace middleware
} // namespace agents
#endif
