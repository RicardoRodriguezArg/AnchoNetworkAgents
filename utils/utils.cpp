#include "utils.h"
#include <array>
#include <iostream>

namespace agents {
namespace utils {

std::optional<std::string> UnpackMessage(const std::string_view input_message) {
  std::optional<std::string> result{};
  if (input_message.empty()) {
    return result;
  }

  std::uint32_t enconded_message_size = 0;
  const auto raw_input_pointer = std::string(input_message).c_str();
  std::memcpy(&enconded_message_size, raw_input_pointer, MESSAGE_SIZE_DEFAULT);

  if ((enconded_message_size) > std::numeric_limits<std::uint32_t>::max()) {
    return result;
  }

  if ((enconded_message_size + 4U) >
      std::numeric_limits<std::uint32_t>::max()) {
    return result;
  }
  return result;
}

bool PackMessageToString(const std::string_view input_message,
                         PacketBufferIterator packet_message_iterator) {
  bool result{false};

  if (input_message.empty()) {
    return result;
  }

  const std::uint32_t message_size = input_message.size();

  if ((message_size + 4U) >= MAX_BUFFER_SIZE) {
    return result;
  }

  // pack the string into a bigger string
  std::memcpy(packet_message_iterator, &message_size, MESSAGE_SIZE_DEFAULT);
  std::memcpy((packet_message_iterator + MESSAGE_SIZE_DEFAULT),
              input_message.data(), message_size);
  result = true;
  return result;
}

std::optional<std::uint32_t> GetPackectMessageSize(
    PacketBufferIterator packet_message_iterator) {
  std::optional<std::uint32_t> result{};
  std::uint32_t enconded_message_size = 0;
  std::memcpy(&enconded_message_size, packet_message_iterator,
              MESSAGE_SIZE_DEFAULT);
  result = enconded_message_size;
  return result;
}

std::optional<std::string> GetPackectMessageData(
    PacketBufferIterator packet_message_iterator, MessageSize message_size) {
  std::optional<std::string> result{};
  if (message_size == 0U) {
    return result;
  }
  std::string raw_data{};
  raw_data.assign(static_cast<char *>(packet_message_iterator), static_cast<int>(message_size));
  result = std::move(raw_data);
  return result;
}

}  // namespace utils
}  // namespace agents
