#ifndef _ETH_LAYER_SOCKET_UDP_SERVER_H__
#define _ETH_LAYER_SOCKET_UDP_SERVER_H__
#include "util.h"
#include <cstdint>

namespace agents {
  namespace communication {
    namespace udp {

      class Server {
      public:
        explicit Server(std::uint16_t port);
        ~Server();
        void InitServer();
        void StopServer();
        std::int32_t ReadFromAllClients(char* buffer,
                                        std::size_t max_message_size) const;

      private:
        void InitSocketFileDescriptor();
        void CreateBasicConfigServerSetup();
        void BindSocketWithServerAddress();

        std::int32_t socket_;
        std::uint16_t port_;
        struct addrinfo server_address_;
      };

    } // namespace udp
  }   // namespace communication
} // namespace agents

#endif
