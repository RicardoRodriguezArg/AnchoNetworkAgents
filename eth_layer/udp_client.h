#ifndef _ETH_LAYER_SOCKET_UDP_CLIENT_H__
#define _ETH_LAYER_SOCKET_UDP_CLIENT_H__
#include "commons/commons.h"
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

namespace agents {
  namespace communication {
    namespace udp {
      class Client {
      public:
        explicit Client(const std::string& addr, std::uint16_t port);
        ~Client();
        void InitClient();
        std::int32_t SendTo(const char* msg, std::size_t size);

      private:
        std::int32_t socket_file_descriptor_;
        std::uint16_t port_;
        const std::string server_address_;
        struct addrinfo client_address_info_;
      };

    } // namespace udp
  }   // namespace communication
} // namespace agents
#endif
