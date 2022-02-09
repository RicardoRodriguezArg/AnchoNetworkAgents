#include "udp_client.h"
#include "util.h"
#include <cstdint>

namespace agents {
  namespace communication {
    namespace udp {

      Client::Client(const std::string& server_addr, std::uint16_t port) :
          port_(port), server_address_(server_addr) {}

      void Client::InitClient() {
        socket_file_descriptor_ =
          agents::communication::CreateUDPFileDescriptor();
        if (!agents::communication::IsValidSocketFileDescriptor(
              socket_file_descriptor_)) {
          throw std::invalid_argument("could not create UDP Client FD socket");
        }
        const bool result = agents::communication::FillUDPClientWithServerInfo(
          client_address_info_, server_address_, port_);
        if (!result) {
          throw std::invalid_argument("could not retreive server information");
        }
      }

      std::int32_t Client::SendTo(const char* message_to_send,
                                  std::size_t message_size) {
        const auto result = ::sendto(
          socket_file_descriptor_, message_to_send, message_size, MSG_CONFIRM,
          client_address_info_.ai_addr, sizeof(client_address_info_));
        return static_cast<std::int32_t>(result);
      }

      Client::~Client() {
        // CloseSock(socket_file_descriptor_, &client_address_info_);
      }

    } // namespace udp
  }   // namespace communication
} // namespace agents
