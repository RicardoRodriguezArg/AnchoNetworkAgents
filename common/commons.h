#ifndef __AGENT_COMMONS_H_
#define __AGENT_COMMONS_H_
#include <functional>

namespace agents {
  namespace common {
    enum class DeviceType : std::uint8_t { UdpServer, RouterTpLink, Camera };

    enum class MessageType : std::uint8_t {
      EVENT = 0U,
      COMAND,
      DATA,
      VIDEO,
      COUNT
    };

    enum class ServerType : std::uint8_t { TCP, UDP };

    using MessageHandlerType = std::function<void(const std::string&)>;

  } // namespace common
} // namespace agents
#endif
