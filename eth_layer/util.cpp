#include "util.h"
#include <cstring>

namespace agents {
  namespace communication {
    // TODO: this is the value of AF_UNSPE=, this socket will accept all
    // protocol
    std::int32_t CreateUDPFileDescriptor() {
      int ai_family = 0;
      return ::socket(ai_family, ::SOCK_DGRAM | ::SOCK_CLOEXEC, ::IPPROTO_UDP);
    }

    bool IsValidSocketFileDescriptor(std::int32_t socket_file_descriptor) {
      return socket_file_descriptor < 0;
    }

    void FillUDPServerInfo(struct ::addrinfo* socket_info, std::uint16_t port) {
      // TODO: change to std
      memset(socket_info, 0, sizeof(*socket_info));
      // Filling server information
      const auto ai_family_value = static_cast<std::int32_t>(AF_UNSPEC);
      socket_info->ai_family = ai_family_value;
      ; // accpets all protocols
      socket_info->ai_socktype = ::SOCK_DGRAM;
      socket_info->ai_protocol = ::IPPROTO_UDP;
    }

    bool BindFileDescriptorSocketWithAddressInfo(
      struct addrinfo* socket_info, std::int32_t socket_file_descriptor) {
      return ::bind(socket_file_descriptor, socket_info->ai_addr,
                    sizeof(*socket_info)) < 0;
    }

    bool FillUDPClientWithServerInfo(struct addrinfo* socket_info,
                                     const std::string& server_port,
                                     std::uint16_t port) {
      std::stringstream decimal_port;
      decimal_port << port;
      std::string port_str(decimal_port.str());
      struct ::addrinfo hints;
      std::memset(&hints, 0, sizeof(hints));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = ::SOCK_DGRAM;
      hints.ai_protocol = ::IPPROTO_UDP;
      const auto result{::getaddrinfo(
        server_port.c_str(), port_str.c_str(), &hints, &socket_info)};

      const auto was_successed = (result == 0);
      return was_successed;
    }

    void CloseSock(std::int32_t socket, struct addrinfo* sock_address) {
      ::freeaddrinfo(sock_address);
      ::close(socket);
    }

  } // namespace communication
} // namespace agents
