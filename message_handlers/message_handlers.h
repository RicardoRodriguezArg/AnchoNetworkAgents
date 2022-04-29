#ifndef __MESSAGE_HANDLER_H_
#define __MESSAGE_HANDLER_H_
#include "commons/commons.h"
#include <glog/logging.h>
namespace agents {
  namespace handlers {

    /**
     * @brief      { struct_description }
     */
    struct MessageHandlerManger {
      using MessageHandlerType = agents::common::MessageHandlerType;
      /**
       * @brief      { function_description }
       *
       * @param[in]  message_type              The message type
       * @param[in]  specific_message_handler  The specific message handler
       *
       * @tparam     MessageType               { description }
       *
       * @return     { description_of_the_return_value }
       */

      bool RegisterMessageHandler(common::MessageType message_type,
                                  std::function<void(const std::string&)> specific_message_handler) {
        const auto message_type_index = static_cast<std::uint8_t>(message_type);
        bool result = false;
        if (message_type_index < message_handler_container_.size()) {
          message_handler_container_[message_type_index] = specific_message_handler;
          result = true;
        }
        return result;
      }

      void HandleMessage(common::MessageType message_type, const std::string& raw_message) {
        if (!message_handler_container_.empty() && message_type < common::MessageType::COUNT) {

          const auto& handler = message_handler_container_[static_cast<std::uint8_t>(message_type)];
          if (handler.has_value()) {
            handler.value()(raw_message);
          }
        } else {
          LOG(ERROR) << "No Message handler defined for Message Type Number: "
                     << std::to_string(static_cast<std::uint8_t>(message_type));
        }
      }

      std::array<std::optional<MessageHandlerType>, static_cast<std::uint8_t>(common::MessageType::COUNT)>
        message_handler_container_;
    };

  } // namespace handlers
} // namespace agents
#endif
