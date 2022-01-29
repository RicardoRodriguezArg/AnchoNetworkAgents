#ifndef _ETH_LAYER_UTILS_H__
#define _ETH_LAYER_UTILS_H__

#include <cstdint>

namespace agents {
  namespace communication {

    std::int32_t CreateUDPFileDescriptor();
    bool IsValidSocketFileDescriptor(std::int32_t socket_file_descriptor);
    void FillUDPServerInfo(struct sockaddr_info* socket_info,
                           std::uint16_t port);
    bool FillUDPClientWithServerInfo(struct sockaddr_info* socket_info,
                                     const std::string& server_port,
                                     std::uint16_t port);
    bool BindFileDescriptorSocketWithAddressInfo(
      struct sockaddr_info* socket_info, std::int32_t socket_file_descriptor);

  } // namespace communication
} // namespace agents
#endif