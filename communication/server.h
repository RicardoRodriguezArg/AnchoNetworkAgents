#ifndef __AGENTS_MIDDLEWARE_SERVER_H_
#define __AGENTS_MIDDLEWARE_SERVER_H_
#include "commons/commons.h"
#include "eth_layer/udp_server.h"
#include "message_handlers/message_handlers.h"
#include "utils/utils.h"
#include <algorithm>
#include <glog/logging.h>
// x86
namespace agents {
  namespace middleware {

    /**
     * @brief      This class describes general agent server in which it will
     * open one socks, it will handle all message in with a custom protocol to avoid consuming more resources from the
     * OS.
     * Implementation of the REACTOR Pattern
     */

    class Server {
    public:
      using MessageHandlerMangerType = agents::handlers::MessageHandlerManger;
      using UdpServerType = agents::communication::udp::Server;
      explicit Server(const agents::handlers::MessageHandlerManger& message_handler, const std::uint16_t server_port) :
        message_handler_(message_handler), udp_server_(server_port) {}

      void CleanInputBuffer() {
        std::fill_n(buffer_.begin(), agents::utils::MAX_BUFFER_SIZE, 0);
        buffer_[agents::utils::MAX_BUFFER_SIZE - 1U] = '\0';
      }

      ~Server() { Stop(); }

      void Init() {
        LOG(INFO) << "Init Server";
        CleanInputBuffer();
        udp_server_.InitServer();
      }

      void Stop() {
        LOG(INFO) << "Stopping Server";
        is_server_operating_ = false;
        udp_server_.StopServer();
        LOG(INFO) << "Stopping udp Server";
        CleanInputBuffer();
      }

      // main pooling function
      void Start() {
        LOG(INFO) << "Starting Server";
        is_server_operating_ = true;
        while (is_server_operating_) {
          const auto number_of_bytes = udp_server_.ReadFromAllClients(buffer_.begin(), agents::utils::MAX_BUFFER_SIZE);
          // Get Message Type
          const auto message_type_opt =
            agents::utils::GetPackectMessageType(buffer_.begin() + agents::utils::MESSAGE_SIZE_DEFAULT);
          if (message_type_opt.has_value()) {
            std::string raw_message_copy{buffer_.begin(), buffer_.begin() + number_of_bytes};
            // TODO:Create Function to handle this transformation
            const auto message_type = static_cast<agents::common::MessageType>(message_type_opt.value());
            message_handler_.HandleMessage(message_type, raw_message_copy);
          }
        }
      }

    private:
      agents::utils::PacketBuffer buffer_;
      MessageHandlerMangerType message_handler_;
      bool is_server_operating_ = true;
      UdpServerType udp_server_;
    };
  } // namespace middleware
} // namespace agents
#endif
