#ifndef __AGENT_SERVER_H_
#define __AGENT_SERVER_H_
#include <array>
#include "../ext_libs/netLink-v1.0.0/netLink/include/netlink/socket.h"
// x86
namespace agents {
namespace server {
enum class ServerType : std::uint8_t { Event, Commands, Data };
/**
 * @brief      This class describes general agent server in which it will open
 * three sockets one for event input/output one for command input/output one for
 * data to transport input/output.
 */
template <class MessageHandler>
class AgentServer {
 public:
  explitcit AgentServer(std::uint16_t server_port,
                        const MessageHandler &message_handler)
      : socket_(server_port), message_handler_(message_handler) {
    server_buffer_[255] = '\0';
  }
  void Init() { NL::init(); }
  void Stop() { is_server_operating_ = false; }
  void Start() {
    clientConnection = server.accept();
    while (clientConnection->read(buffer, 255)) {
      // Get Message
      // Check Protocol
      // De-Serialize
      // Send to the message handler
      // save to DB
    }
  }

 private:
  std::array<256U, char> server_buffer_;
  const NL::Socket socket_;
  const MessageHandler &message_handler_;
  NL::Socket *clientConnection = std::nullptr;
  volatile bool is_server_operating_ = true;
};
}  // namespace server
}  // namespace agents
#endif