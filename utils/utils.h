#ifndef __AGENT_UTILS_H_
#define __AGENT_UTILS_H_

#include <array>
#include <cstring>
#include <limits>
#include <optional>
#include <string_view>

namespace agents {
namespace utils {

static constexpr std::uint8_t MAX_MESSAGE_SIZE = 4U;

/**
 * @brief      Utils function to unpack a recieved message according
 *             to the protocol:
 *             First 4 Bytes of the input messaage is size of the encoded
 *             message encoded message = sizeof(string_message) - 4 Bytes
 *
 * @param[in]  input_message  The input message
 *
 * @return     { description_of_the_return_value }
 */

std::optional<std::string> UnpackMessage(const std::string_view input_message) {
  std::optional<std::string_view> result{};
  if (input_message.empty()) {
    return result;
  }

  std::uint32_t enconded_message_size = 0;
  const auto raw_input_pointer = std::string(input_message).c_str();
  std::memcpy(&enconded_message_size, raw_input_pointer, MAX_MESSAGE_SIZE);

  if ((enconded_message_size) > std::numeric_limits<std::uint32_t>::max()) {
    return result;
  }

  if ((enconded_message_size + 4U) >
      std::numeric_limits<std::uint32_t>::max()) {
    return result;
  }

  std::string_view raw_message{};
  std::memcpy(&raw_message, raw_input_pointer + MAX_MESSAGE_SIZE,
              input_message.size());
  return result;
}

/**
 * @brief      Pack Input String view into our protocol
 *
 * @param[in]  input_message  The input message
 *
 * @return     { packet message (4 bytes) + size of packet message }
 */
std::optional<std::string> PackMessageToString(
    const std::string_view input_message) {
  std::optional<std::string> result{};

  if (input_message.empty()) {
    return result;
  }
  const auto message_size = input_message.size();

  if ((message_size + 4U) >= 512U) {
    return result;
  }

  std::string packet_output_string{message_size + 4U,''};
  // pack the string into a bigger string
  std::memcpy(packet_output_string.c_str(), &message_size, MAX_MESSAGE_SIZE);
  std::memcpy(packet_output_string.c_str() + MAX_MESSAGE_SIZE,
              input_message.c_str(), message_size);
  result = std::optional<std::string>{packet_output_string};
  return result;
}
}  // namespace utils

}  // namespace agents
}  // namespace agents
#endif
