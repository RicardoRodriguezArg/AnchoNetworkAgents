#include "utils.h"

namespace agents {
namespace utils {

std::optional<std::string> UnpackMessage(const std::string_view input_message) {
  std::optional<std::string> result{};
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
}

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

  std::string packet_output_string;
  // pack the string into a bigger string
  std::memcpy(static_cast<void *>(packet_output_string.data()), &message_size,
              MAX_MESSAGE_SIZE);
  std::memcpy(
      static_cast<void *>(packet_output_string.data() + MAX_MESSAGE_SIZE),
      input_message.data(), message_size);
  result = std::optional<std::string>{packet_output_string};
  return result;
}

}  // namespace utils