#include "udp_client.h"
#include "utils.h"

namespace agents {
namespace communication {
namespace udp {

Client::Client(const std::string &server_addr, int port)
    : port_(port), addr_(server_addr) {}

void Client::InitClient() {
  socket_file_descriptor_ = agents::communication::CreateUDPFileDescriptor();
  if (!agents::communication::IsValidSocketFileDescriptor(
          socket_file_descriptor_)) {
    throw std::invalid_argument("could not create UDP Client FD socket");
  }
  const bool result = agents::communication::FillUDPClientWithServerInfo(
      server_info_, addr_, port_);
  if (!result) {
    throw std::invalid_argument("could not retreive server information");
  }
}

void Client::SendTo(const char *message_to_send, std::int32_t message_size) {
  ::sendto(socket_file_descriptor_, message_to_send, message_size, MSG_CONFIRM,
           server_info_, sizeof(*server_info_));
}

Client::~Client() {
  ::freeaddrinfo(addrinfo_);
  ::close(socket_);
}

} // namespace udp
} // namespace communication
} // namespace agents