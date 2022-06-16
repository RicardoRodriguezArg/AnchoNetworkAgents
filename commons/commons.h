#ifndef __AGENT_COMMONS_H_
#define __AGENT_COMMONS_H_
#include <functional>

namespace agents {
  namespace common {
    enum class DeviceType : std::uint8_t { UdpServer, RouterTpLink, Camera };

    enum class DeviceId : std::uint8_t { MainUdpServer };

    // TODO:This need to be in-sync with general interface definition (proto file definition)
    enum class MessageType : std::uint8_t { EVENT = 0U, COMAND_NANO, COMMAND_PROTO, DATA, VIDEO, COUNT };

    enum class ServerType : std::uint8_t { TCP, UDP };

    using MessageHandlerType = std::function<void(const std::string&)>;
    static constexpr std::uint16_t MAX_MESSAGE_COUNT{500U};

  } // namespace common
} // namespace agents
#endif
