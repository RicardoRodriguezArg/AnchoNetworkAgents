#ifndef _ETH_LAYER_UTILS_H__
#define _ETH_LAYER_UTILS_H__

#include <arpa/inet.h>
#include <cstdint>
#include <glog/logging.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace agents {
  namespace communication {

    std::int32_t CreateUDPFileDescriptor();
    bool IsValidSocketFileDescriptor(std::int32_t socket_file_descriptor);
    void FillUDPServerInfo(struct addrinfo* socket_info, std::uint16_t port);
    struct ::sockaddr_in CreateServerAddressInfo(std::uint16_t port, const std::string& server_addr);

    bool FillUDPClientWithServerInfo(struct addrinfo* socket_info, const std::string& server_port, std::uint16_t port);

    bool BindFileDescriptorSocketWithAddressInfo(struct sockaddr_in* socket_info, std::int32_t socket_file_descriptor);

    void CloseOnlySockDescriptor(std::int32_t socket);

  } // namespace communication
} // namespace agents
#endif
