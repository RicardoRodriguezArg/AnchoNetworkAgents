#include "udp_server.h"
#include "util.h"
#include <exception>
#include <glog/logging.h>
#include <stdexcept>

namespace agents {
  namespace communication {
    namespace udp {

      Server::Server(std::uint16_t port) : port_(port) {
        // TODO: Add assert about port length 0-65536
      }

      void Server::InitSocketFileDescriptor() {
        LOG(INFO) << "Creating udp file descriptor";
        socket_ = agents::communication::CreateUDPFileDescriptor();
        if (agents::communication::IsValidSocketFileDescriptor(socket_)) {
          LOG(INFO) << "Throwing Exception!";
          throw std::invalid_argument("could not create UDP Server FD socket");
        }
      }

      void Server::BindSocketWithServerAddress() {
        const auto could_bind_file_descriptor =
          agents::communication::BindFileDescriptorSocketWithAddressInfo(&server_address_in_, socket_);
        LOG(INFO) << "Bind result: " << std::to_string(could_bind_file_descriptor);
        if (!could_bind_file_descriptor) {
          throw std::invalid_argument("could not bind FD Socket with Server Address");
        }
      }

      void Server::InitServer() {
        LOG(INFO) << "ETH Init sockets files descriptors";
        InitSocketFileDescriptor();
        server_address_in_ = CreateServerAddressInfo(port_, server_ip_address_);
        BindSocketWithServerAddress();
        is_operating_ = true;
      }

      std::int32_t Server::ReadFromAllClients(char* buffer, std::size_t max_message_size) const {
        const auto last_message_byte = ::recv(socket_, buffer, max_message_size, 0);
        buffer[last_message_byte] = '\0';
        return last_message_byte;
      }

      void Server::StopServer() {
        LOG(INFO) << "Stop Sockect : " << std::to_string(socket_);
        if (is_operating_) {
          CloseOnlySockDescriptor(socket_);
        }
        is_operating_ = false;
      }

      Server::~Server() {
        if (is_operating_) {
          StopServer();
          is_operating_ = true;
        }
      }

    } // namespace udp
  }   // namespace communication
} // namespace agents
