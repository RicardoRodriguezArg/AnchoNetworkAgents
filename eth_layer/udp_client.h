#ifndef _ETH_LAYER_SOCKET_UDP_CLIENT_H__
#define _ETH_LAYER_SOCKET_UDP_CLIENT_H__
#include "commons.h"
#include <string>

namespace agents {
  namespace communication {
    namespace udp {
      class Client {
      public:
        explicit Client(const std::string& addr, std::uint16_t port);
        ~Client();
        void InitClient();
        std::int32_t SendTo(const char* msg, size_t size);

      private:
        std::int32_t socket_file_descriptor_;
        std::uint16_t port_;
        std::string address_;
        struct addrinfo* server_info_ = nullptr;
      };

    } // namespace udp
  }   // namespace communication
} // namespace agents