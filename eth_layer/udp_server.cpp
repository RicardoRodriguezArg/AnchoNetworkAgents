#include "udp_server.h"
#include "util.h"
#include <arpa/inet.h>
#include <errno.h>
#include <exception>
#include <glog/logging.h>
#include <netdb.h>
#include <stdexcept>
#include <sys/fcntl.h>

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
        LOG(INFO) << "Init sockets files descriptors";
        InitSocketFileDescriptor();
        server_address_in_ = CreateServerAddressInfo(port_, server_ip_address_);
        BindSocketWithServerAddress();
        LOG(INFO) << "Set socket as non blocking";
        const auto result = SetFlagToNonBlocking();
        LOG(INFO) << "Set socket as non blocking - Result" << std::to_string(result);
        is_operating_ = true;
      }

      std::int32_t Server::SetFlagToNonBlocking() {
        std::int32_t flags = fcntl(socket_, F_GETFL);
        std::int32_t result = ::fcntl(socket_, F_SETFL, flags | O_NONBLOCK);
        return result;
      }

      std::int32_t Server::ReadFromAllClients(char* buffer, std::size_t max_message_size) const {
        struct sockaddr_in client_addr;
        std::memset(buffer, '\0', sizeof(*buffer));
        std::uint32_t client_struct_length = sizeof(client_addr);
        const auto last_message_byte =
          ::recvfrom(socket_, buffer, sizeof(*buffer), 0, (struct sockaddr*)&client_addr, &client_struct_length);
        // buffer[last_message_byte] = '\0';
        LOG(INFO) << "last message byte: " << std::to_string(last_message_byte);
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
