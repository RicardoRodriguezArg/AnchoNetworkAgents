#include "utils/utils.h"
#include <unistd.h>

namespace agents {
  namespace communication {

    std::int32_t CreateUDPFileDescriptor() {
      return ::socket(::AF_INET, ::SOCK_DGRAM | ::SOCK_CLOEXEC, ::IPPROTO_UDP);
    }

    bool IsValidSocketFileDescriptor(std::int32_t socket_file_descriptor) {
      return socket_file_descriptor < 0;
    }

    void FillUDPServerInfo(struct ::addrinfo* socket_info, std::uint16_t port) {
      // TODO: change to std
      memset(socket_info, 0, sizeof(*socket_info));
      // Filling server information
      socket_info->sin_family = ::AF_INET; // IPv4
      socket_info->sin_addr.s_addr = ::INADDR_ANY;
      socket_info->sin_port = ::htons(port);
    }

    bool BindFileDescriptorSocketWithAddressInfo(
      struct addrinfo* socket_info, std::int32_t socket_file_descriptor) {
      return ::bind(socket_file_descriptor, socket_info, sizeof(*socket_info)) <
             0;
    }

    bool FillUDPClientWithServerInfo(struct addrinfo& socket_info,
                                     const std::string& server_port,
                                     std::uint16_t port) {
      std::stringstream decimal_port;
      decimal_port << port;
      std::string port_str(decimal_port.str());
      struct ::addrinfo hints;
      std::memset(&hints, 0, sizeof(hints));
      hints.ai_family = ::AF_UNSPEC;
      hints.ai_socktype = ::SOCK_DGRAM;
      hints.ai_protocol = ::IPPROTO_UDP;
      const auto result{
        ::getaddrinfo(addr.c_str(), port_str.c_str(), &hints, socket_info)};

      const auto was_successed = (result == 0);
      return was_successed;
    } // namespace communication

    void CloseSock(std::int32_t socket, struct addrinfo* sock_address) {
      ::freeaddrinfo(sock_address);
      ::close(socket);
    }

  } // namespace communication
} // namespace agents
