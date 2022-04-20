#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMONS_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMONS_H_
#include "interface/message_interface_idl.pb.h"
#include "interface/pb_decode.h"
#include "interface/pb_encode.h"
#include <cstring>

namespace agents {
  namespace middleware {

    struct DataDecoder {

      ::agent_interface_CommandWithArguments DecodeToCommand(const std::string& raw_data_input) {
        ::agent_interface_CommandWithArguments command_with_argument{};
        std::memcpy(buffer_, raw_data_input.c_str(), raw_data_input.size());
        auto stream = pb_istream_from_buffer(buffer_, raw_data_input.size());
        pb_decode(&stream, pb_field_, &command_with_argument);
        return command_with_argument;
      }

      std::string EncodeCommand(const ::agent_interface_CommandWithArguments& command_to_encode) {
        std::string result{};
        stream_ = ::pb_ostream_from_buffer(buffer_, agents::common::MAX_MESSAGE_COUNT);
        if (pb_encode(&stream_, pb_field_, &command_to_encode)) {
          result.assign(reinterpret_cast<char*>(buffer_), stream_.bytes_written);
        }
        return result;
      }

      ::_agent_interface_Event DecodeToEvent(const std::string& raw_data_input) {
        ::_agent_interface_Event event{};
        std::memcpy(buffer_, raw_data_input.c_str(), raw_data_input.size());
        auto istream = pb_istream_from_buffer(buffer_, raw_data_input.size());
        agent_interface_CommandWithArguments command_with_argument;
        pb_decode(&istream, pb_field_, &command_with_argument);
        return event;
      }

      std::uint8_t buffer_[agents::common::MAX_MESSAGE_COUNT];
      pb_msgdesc_t* pb_field_;
      ::pb_ostream_t stream_;
    };
  } // namespace middleware
} // namespace agents
#endif
