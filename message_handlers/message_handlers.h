#ifndef __MESSAGE_HANDLER_H_
#define __MESSAGE_HANDLER_H_
namespace agents {
  namespace handlers {

    /**
     * @brief      { struct_description }
     */
    struct MessageHandlerManger {
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
      template <typename MessageType>
      bool RegisterMessageHandler(
        common::MessageType message_type,
        const std::function<void(const std::string_view&)>&
          specific_message_handler) {
        message_handler_container_[static_cast<std::uint8_t>(message_type)] =
          specific_message_handler;
      }

      void HandleMessage(common::MessageType message_type,
                         const std::string& raw_message) {
        const auto& handler =
          message_handler_container_[static_cast<std::uint8_t>(message_type)];
        if (handler.has_value()) {
          handler.value()(raw_message);
        }
      }

      std::array<static_cast<std::uint8_t>(common::MessageType::COUNT),
                 std::optional<MessageHandlerType>>
        message_handler_container_;
    };

  } // namespace handlers
} // namespace agents
#endif
