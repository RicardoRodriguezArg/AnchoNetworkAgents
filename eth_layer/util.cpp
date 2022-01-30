#include "utils.h"
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace agents {
  namespace communication {

    std::int32_t CreateUDPFileDescriptor() {
  return ::socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP));
    }

    bool IsValidSocketFileDescriptor(std::int32_t socket_file_descriptor) {
      return socket_file_descriptor < 0;
    }

    void FillUDPServerInfo(struct sockaddr_info* const socket_info,
                           std::uint16_t port) {
      memset(socket_info, 0, sizeof(*socket_info));
      // Filling server information
      server_address_->sin_family = AF_INET; // IPv4
      server_address_->sin_addr.s_addr = INADDR_ANY;
      server_address_->sin_port = htons(port);
    }

    bool BindFileDescriptorSocketWithAddressInfo(
      struct sockaddr_info* socket_info, std::int32_t socket_file_descriptor) {
      return ::bind(socket_file_descriptor, socket_info, sizeof(*socket_info)) <
             0;
    }

    bool FillUDPClientWithServerInfo(struct sockaddr_info* socket_info,
                                     const std::string& server_port,
                                     std::uint16_t port) {
      std::stringstream decimal_port;
      decimal_port << port;
      std::string port_str(decimal_port.str());
      struct addrinfo hints;
      memset(&hints, 0, sizeof(hints));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_DGRAM;
      hints.ai_protocol = IPPROTO_UDP;
      const auto result(
        getaddrinfo(addr.c_str(), port_str.c_str(), &hints, socket_info));
      const auto was_successed = (result == 0 || socket_info != std::nullptr);
      return was_successed;
    }
  } // namespace communication
} // namespace agents
