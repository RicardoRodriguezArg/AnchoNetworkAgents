#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_DATA_MESSAGES_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_DATA_MESSAGES_H_
#include "data_processors/data_processor_commons.h"
#include <array>
#include <optional>
namespace agents {
  namespace middleware {

    template <typename MessageType>
    struct MessageDictionary {
      explicit MessageDictionary(
        std::array<MessageType, MAX_MESSAGE_COUNT> array_from_factory) :
          message_array_(std::move(array_from_factory)) {}

      std::optional<MessageType> GetMessageFromDictionary(
        const std::uint32_t message_id) {
        // TODO:
        std::optional<MessageType> result{};
        if (message_id > 0 && message_id < MAX_MESSAGE_COUNT) {
          return message_array_[message_id];
        }
        return result;
      }

      std::array<MessageType, MAX_MESSAGE_COUNT> message_array_;
    }; // namespace middleware

  } // namespace middleware
} // namespace agents
#endif
