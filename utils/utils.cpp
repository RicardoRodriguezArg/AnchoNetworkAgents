#include "utils.h"
#include <iostream>
#include <array>

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
  return result;
}

std::optional<std::string> PackMessageToString(
    const std::string_view input_message) {
  std::optional<std::string> result{};

  if (input_message.empty()) {
    return result;
  }
  const std::uint32_t message_size = input_message.size();

  if ((message_size + 4U) >= 512U) {
    return result;
  }

  std::string packet_output_string;
  std::array<std::uint8_t, 512U> buffer;
  buffer[511]='\n';
  // pack the string into a bigger string
  std::memcpy(buffer.begin(), &message_size, MAX_MESSAGE_SIZE);
  std::cout << "message size: "<< message_size<< std::endl;
  std::cout << "packet message size: "<< packet_output_string << std::endl;
  std::memcpy( (buffer.begin() + MAX_MESSAGE_SIZE), input_message.data(), message_size);
  result = std::optional<std::string>{packet_output_string};
  for (const auto data: buffer )
  {
	  std::cout << std::to_string(data)<< ' ';
  }

  return result;
}

std::optional<std::uint32_t> GetPackectMessageSize(
    std::string_view packet_message) {
  std::optional<std::uint32_t> result{};
  if (packet_message.empty()) {
    return result;
  }
  std::uint32_t enconded_message_size = 0;
  const auto raw_input_pointer = std::string(packet_message).c_str();
  std::memcpy(&enconded_message_size, raw_input_pointer, MAX_MESSAGE_SIZE);
  result = enconded_message_size;
  return result;
}

}  // namespace utils
}  // namespace agents
