#ifndef _ETH_LAYER_SOCKET_H__
#define _ETH_LAYER_SOCKET_H__
#include <string>
#include "eth_layer/commons.h"
namespace agents {
namespace communication {

class Socket {
 public:
  explicit Socket(const std::string& hostTo, std::uint16_t portTo,
                  Protocol protocol = kTCP, IPVer ipVer = kANY);

  explicit Socket(std::uint16_t portFrom, Protocol protocol = kTCP,
                  IPVer ipVer = kIP4, const std::string& hostFrom = "",
                  std::uint16_t listenQueue = DEFAULT_LISTEN_QUEUE);

  explicit Socket(const std::string& hostTo, std::uint16_t portTo,
                  std::uint16_t portFrom, IPVer ipVer = kANY);

  ~Socket();

  Socket accept();

  int read(void* buffer, size_t bufferSize);
  void send(const void* buffer, size_t size);

  int readFrom(void* buffer, size_t bufferSize, string* HostFrom,
               std::uint16_t* portFrom = NULL);
  void sendTo(const void* buffer, size_t size, const string& hostTo,
              std::uint16_t portTo);

  int nextReadSize() const;

  void disconnect();

  std::string_view GetHostTo() const { return hostTo_; }

  std::string_view GetHostFrom() const { return hostFrom_; }

  std::uint16_t GetportTo() const { return portTo_; }

  std::uint16_t GetportFrom() const { return portFrom_; }

  Protocol Getprotocol() const { return protocol_; }

  IPVer GetipVer() const { return ipVer_; }

  SocketType Gettype() const { return type_; }

  std::uint16_t GetlistenQueue() const { return listenQueue_; }

  bool Getblocking() const { return blocking_; }

  int GetsocketHandler() const { return socketHandler_; }

  void blocking(bool blocking);

 private:
  void Initialize();

  std::int32_t socketHandler_;
  std::uint16_t portTo_;
  std::uint16_t portFrom_;
  std::uint16_t listenQueue_;
  Protocol protocol_;
  IPVer ipVer_;
  SocketType type_;
  bool _blocking_;
  std::string hostTo_;
  std::string hostFrom_;
};
}  // namespace communication
}  // namespace agents

#endif
