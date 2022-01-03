#ifndef __AGENT_SERVER_H_
#define __AGENT_SERVER_H_
#include <algorithm>
#include <atomic>

#include "../ext_libs/netLink-v1.0.0/netLink/include/netlink/socket.h"
#include "common/commons.h"
#include "message_handler/message_handler.h"
// x86
namespace agents {
namespace server {

/**
 * @brief      This class describes general agent server in which it will open
 * three sockets one for event input/output one for command input/output one for
 * data to transport input/output.
 */

class AgentServer {
 public:
  explicit AgentServer(common::ServerType server_type,
                       std::uint16_t server_port)
      : socket_(server_port) {}

  void CleanInputBuffer() {
    std::fill_n(raw_buffer_.begin(), agents::utils::MAX_BUFFER_SIZE, 0);
    raw_buffer_[511] = '\0';
  }

  void Init() { NL::init(); }
  void Stop() { is_server_operating_ = false; }
  void Start() {
    clientConnection = server.accept();
    while (clientConnection->read(buffer, 255)) {
      // Get Message
      // Get Message Type
      // De-Serialize
      // Send to the specific message handler
      // save to DB
    }
  }

 private:
  agents::utils::PacketBuffer raw_buffer_;
  const NL::Socket socket_;
  const MessageHandler &message_handler_;
  NL::Socket *clientConnection = std::nullptr;
  std::atomic<bool> is_server_operating_ = true;
  common::ServerType server_type;
};
}  // namespace server
}  // namespace agents
#endif