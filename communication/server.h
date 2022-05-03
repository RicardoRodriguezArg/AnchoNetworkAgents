#ifndef __AGENTS_MIDDLEWARE_SERVER_H_
#define __AGENTS_MIDDLEWARE_SERVER_H_
#include "commons/commons.h"
#include "eth_layer/udp_server.h"
#include "message_handlers/message_handlers.h"
#include "utils/utils.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <glog/logging.h>
#include <thread>
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

      ~Server() {
        Stop();
        working_thread_.join();
      }

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

      void StartServerThread() {
        if (!is_server_operating_) {
          is_server_operating_ = true;
          LOG(INFO) << "Creating Server Thread";
          working_thread_ = std::thread(&Server::RunServer, this);
        }
      }

    private:
      // main pooling function
      void RunServer() {
        using namespace std::chrono_literals;
        LOG(INFO) << "Starting Server";
        while (is_server_operating_) {
          LOG(INFO) << "Reading from all client";
          buffer_[agents::utils::MAX_BUFFER_SIZE - 1U] = '\0';
          const auto number_of_bytes = udp_server_.ReadFromAllClients(buffer_.begin(), agents::utils::MAX_BUFFER_SIZE);
          LOG(INFO) << "Number of bytes: " << std::to_string(number_of_bytes);
          if (number_of_bytes > 0) {
            LOG(INFO) << "Parsing Message GetMessageType: ";

            const auto message_type_opt =
              agents::utils::GetPackectMessageType(buffer_.begin() + agents::utils::MESSAGE_SIZE_DEFAULT);
            const auto message_size_opt = agents::utils::GetPackectMessageSize(buffer_.begin());
            if (message_type_opt.has_value() && message_size_opt.has_value()) {

              LOG(INFO) << "Parsed Message Size: " << std::to_string(message_size_opt.value());
              const auto raw_message_copy = agents::utils::GetPackectMessageData(
                buffer_.begin() + agents::utils::MESSAGE_SIZE_DEFAULT + agents::utils::MESSAGE_TYPE_SIZE,
                message_size_opt.value());

              const auto message_type = static_cast<agents::common::MessageType>(message_type_opt.value());
              LOG(INFO) << "Parsed Message Type: " << std::to_string(message_type_opt.value());
              if (raw_message_copy.has_value()) {
                message_handler_.HandleMessage(message_type, raw_message_copy.value());
              }
            }
          } else {
            LOG(INFO) << "Server is sleeping";
            std::this_thread::sleep_for(2000ms);
          }
        }

        LOG(INFO) << "Server is stopped";
        is_server_operating_ = false;
      }

      void CleanInputBuffer() {
        std::fill_n(buffer_.begin(), agents::utils::MAX_BUFFER_SIZE, 0);
        buffer_[agents::utils::MAX_BUFFER_SIZE - 1U] = '\0';
      }

      agents::utils::PacketBuffer buffer_;
      MessageHandlerMangerType message_handler_;
      std::atomic<bool> is_server_operating_ = false;
      UdpServerType udp_server_;
      std::thread working_thread_;
    };
  } // namespace middleware
} // namespace agents
#endif
