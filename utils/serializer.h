#ifndef __AGENT_UTILS_SERIALIZER_H_
#define __AGENT_UTILS_SERIALIZER_H_

#include "interface/message_interface_idl.pb.nano.h"
#include "interface/pb_common.h"
#include "interface/pb_decode.h"
#include "interface/pb_encode.h"

#include <optional>

namespace agents {
  namespace utils {
    struct Serializer {

      std::optional<agent_interface_CommandWithArguments> DeSerializeCommandFromString(
        const std::string& raw_input_message) {
        std::optional<agent_interface_CommandWithArguments> result = std::nullopt;
        if (TransferRawMessageToInputBuffer(raw_input_message)) {
          auto pointer_to_buffer = buffer_;
          auto stream = pb_istream_from_buffer(pointer_to_buffer, raw_input_message.size());
          agent_interface_CommandWithArguments command{};
          if (pb_decode(&stream, agent_interface_CommandWithArguments_fields, &command)) {
            result = command;
          }
        }

        return result;
      }

    private:
      void CleanInputBuffer() { std::memset(buffer_, '\0', sizeof(buffer_)); }

      bool TransferRawMessageToInputBuffer(const std::string& raw_input_message) {
        if (raw_input_message.empty()) {
          return false;
        }
        if (raw_input_message.size() > kBufferSize) {
          // TODO:Log error here
          return false;
        }
        CleanInputBuffer();
        std::memcpy(buffer_, raw_input_message.c_str(), raw_input_message.size());
        return true;
      }

      static constexpr std::uint8_t kBufferSize{255u};
      pb_byte_t buffer_[kBufferSize];
    };

    // namespace serializer
  } // namespace utils
} // namespace agents
#endif
