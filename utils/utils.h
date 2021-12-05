#ifndef __AGENT_UTILS_H_
#define __AGENT_UTILS_H_
#include "../interface/message_interface_idl.pb.h"
#include <array>
#include <cstring>
#include <optional>

namespace agents {
namespace utils {

static constexpr std::uint8_t MAX_MESSAGE_SIZE = 4U;

std::optional<std::string> UnpackMessage(std::string input_message) {
  std::optional<std::string> result{};
  if (input_message.empty()) {
    return result;
  }
  std::int16_t size_frame = 0;
  std::memcpy(&size_frame, input_message.c_str(), sizeof(MAX_MESSAGE_SIZE));

  if ((size_frame + sizeof(size_frame)) >= MAX_MESSAGE_SIZE) {
    return result;
  }

  std::string raw_message{};

  std::memcpy(&raw_message, input_message.c_str(), si);
  return result;
}

std::optional<agent_interface_Event>
DeSerializeEventMessage(const std::string &raw_message) {
  std::optional<agent_interface_Event> resutl{};
}

} // namespace utils
} // namespace agents
#endif
