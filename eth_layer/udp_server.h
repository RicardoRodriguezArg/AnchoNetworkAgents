#ifndef _ETH_LAYER_SOCKET_UDP_SERVER_H__
#define _ETH_LAYER_SOCKET_UDP_SERVER_H__

namespace agents {
namespace communication {
namespace udp {

class Server {
public:
  explicit Server(std::uint16_t port);
  ~Server();
  void InitServer();
  void ReadFromAllClients();
  std::int32_t ReadFromAllClients(char *buffer,
                                  std::size_t max_message_size) const;

private:
  void CreateSocketFileDescriptor();
  void CreateBasicConfigServerSetup();
  void CreateBasicConfigServerSetup();

  std::int32_t socket_;
  std::uint16_t port_;
  struct sockaddr_in *server_address_ = nullptr;
};

} // namespace udp
} // namespace communication
} // namespace agents

#endif