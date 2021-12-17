#ifndef __AGENT_SERVER_H_
#define __AGENT_SERVER_H_
namespace agents {
namespace event_handler {

enum class MessageType : std::uint8_t { EVENT, COMAND, DATA, VIDEO };

/**
 * @brief      Base Event Handler Class
 *
 * @tparam     SpecificEventHandler  { Template argument speficic for each kind
 * of message type }
 */
template <typename SpecificEventHandler>
struct BaseEventHandler {
  /**
   * @brief      Public Interface of Event Handler
   */
  template <typename InputMessage>
  void interface(const InputMessage& raw_message) {
    static_cast<SpecificEventHandler*>(this)->implementation(raw_message);
  }
};

// Message Handler for Events
template <typename MessageType>
struct MessageHandler : BaseEventHandler<MessageHandler<MessageType>> {};

}  // namespace event_handler
}  // namespace agents
#endif