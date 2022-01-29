#include "udp_server.h"
#include "utils.h"

namespace agents {
  namespace communication {
    namespace udp {

      Server::Server(std::uint16_t port) : port_(port) {
        // TODO: Add assert about port length 0-65536
      }

      void Server::CreateSocketFileDescriptor() {
        socket_ = agents::communication::CreateUDPFileDescriptor();
        if (!agents::communication::IsValidSocketFileDescriptor(socket_)) {
          throw std::invalid_argument("could not create UDP Server FD socket");
        }
      }

      void Server::CreateBasicConfigServerSetup() {
        agents::communication::FillUDPServerInfo(server_address_, port_);
      }

      void Server::BindSocketWithServerAddress() {
        const auto could_bind_file_descriptor =
          agents::communication::BindFileDescriptorSocketWithAddressInfo(
            server_address_, socket_);
        if (!could_bind_file_descriptor) {
          throw std::invalid_argument(
            "could not bind FD Socket with Server Address");
        }
      }

      void Server::InitServer() {
        CreateSocketFileDescriptor();
        CreateBasicConfigServerSetup();
        BindSocketWithServerAddress();
      }

      std::int32_t Server::ReadFromAllClients(
        char* buffer, std::size_t max_message_size) const {
        const auto last_message_byte =
          ::recv(socket_, buffer, max_message_size, 0);
        buffer[last_message_byte] = '\0';
        return last_message_byte;
      }

      Server::StopServer() {
        ::freeaddrinfo(server_address_);
        ::close(socket_);
      }

      Server::~Server() { StopServer() }

    } // namespace udp
  }   // namespace communication
} // namespace agents