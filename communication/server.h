#ifndef __AGENTS_MIDDLEWARE_SERVER_H_
#define __AGENTS_MIDDLEWARE_SERVER_H_
#include <algorithm>

#include "commons/commons.h"
#include "eth_layer/udp_server.h"
#include "message_handlers/message_handlers.h"
#include "utils/utils.h"
// x86
namespace agents {
  namespace middleware {

    /**
     * @brief      This class describes general agent server in which it will
     * open three sockets one for event input/output one for command
     * input/output one for data to transport input/output. Implementation of
     * the REACTOR Pattern
     */

    class Server {
    public:
      explicit Server(const handlers::MessageHandlerManger& message_hanlder,
                      std::uint16_t server_port) :
          message_hanlder_(message_handler),
          udp_socket_(server_port) {}

      void CleanInputBuffer() {
        std::fill_n(
          raw_message_copy.begin(), agents::utils::MAX_BUFFER_SIZE, 0);
        raw_message_copy[agents::utils::MAX_BUFFER_SIZE - 1U] = '\0';
      }

      ~Server() { Stop(); }

      void Init() {
        CleanInputBuffer();
        udp_socket_.InitServer();
      }

      void Stop() {
        is_server_operating_ = false;
        udp_socket_.StopServer();
        CleanInputBuffer();
      }

      void Start() {
        is_server_operating_ = true;
        while (is_server_operating_) {
          const auto number_of_bytes = udp_socket_->ReadFromAllClients(
            buffer_.begin(), agents::utils::MAX_BUFFER_SIZE)
                                       // Get Message Type
                                       const auto message_type_opt =
            agents::utils::GetPackectMessageType(
              raw_buffer_.begin() + agents::utils::MESSAGE_SIZE_DEFAULT);
          if (message_type_opt.has_value()) {
            std::string raw_message_copy{
              buffer_.begin(), buffer_.begin() + number_of_bytes};
            message_handler_.HandleMessage(
              message_type_opt.value(), raw_message_copy);
          }
        }
      }

    private:
      agents::utils::PacketBuffer buffer_;
      const MessageHandler& message_handler_;
      bool is_server_operating_ = true;
      communication::udp udp_socket_;
    };
  } // namespace middleware
} // namespace agents
#endif
