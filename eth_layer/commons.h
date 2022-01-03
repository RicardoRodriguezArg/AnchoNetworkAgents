
#ifndef __ETH_LAYER_COMMONS_H_
#define __ETH_LAYER_COMMONS_H_
namespace agents {
namespace common {

constexpr std::size_t kDEFAULT_LISTEN_QUEUE = 50U;

enum class Protocol : std::uint8_t { kTcp, kUdp };

enum class IPVer : std::uint8_t { kIp4, kIp6, kAny };

enum class SocketType : std::uint8_t { kClient, kServer };

enum class EthErrorCode : std::uint8_t {
  kBadProtocol,
  kBadIpVer,
  kErrorInitialization,
  kErrorSetAddress,
  kErrorGetAddressInfo,
  kErrorSetSockOpt,
  kErrorCanNotListen,
  kErrorConnectSocket,
  kErrorSend,
  kErrorRead,
  kErrorIoctl,
  kErrorSelect,
  kErrorAlloc,
  kExpectedTcpSock,
  kExpectedUdpSock,
  kExpectedClientSock,
  kExpectedServerSock,
  kErrorExpectedHostTo,
  kErrorOutOfRange
};

}  // namespace common
}  // namespace agents
#endif
