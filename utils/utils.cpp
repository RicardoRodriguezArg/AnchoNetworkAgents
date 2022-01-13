#include "utils.h"
#include <array>
#include <iostream>
#include <string_view>

namespace agents {
namespace utils {

bool PackMessageToString(const std::string_view input_message,
                         PacketBufferIterator packet_message_iterator,
                         common::MessageType message_type) {
  bool result{false};

  if (input_message.empty()) {
    return result;
  }

  const std::uint32_t message_size = input_message.size();

  if ((message_size + 4U) >= MAX_BUFFER_SIZE) {
    return result;
  }
  // First 4 bytes pack message size
  std::memcpy(packet_message_iterator, &message_size, MESSAGE_SIZE_DEFAULT);
  // Fith 5 byte pack message type
  std::uint8_t message_type_pack = static_cast<std::uint8_t>(message_type);
  std::memcpy(packet_message_iterator + MESSAGE_SIZE_DEFAULT,
              &message_type_pack, MESSAGE_TYPE_SIZE);
  // pack message to buffer
  std::memcpy(
      (packet_message_iterator + MESSAGE_SIZE_DEFAULT + MESSAGE_TYPE_SIZE),
      input_message.data(), message_size);
  result = true;
  return result;
}

std::optional<std::uint32_t>
GetPackectMessageSize(PacketBufferIterator packet_message_iterator) {
  std::optional<std::uint32_t> result{};
  std::uint32_t enconded_message_size = 0;
  std::memcpy(&enconded_message_size, packet_message_iterator,
              MESSAGE_SIZE_DEFAULT);
  result = enconded_message_size;
  return result;
}

std::optional<std::string>
GetPackectMessageData(PacketBufferIterator packet_message_iterator,
                      MessageSize message_size) {
  std::optional<std::string> result{};
  if (message_size == 0U) {
    return result;
  }
  std::string raw_data{};
  raw_data.assign(static_cast<char *>(packet_message_iterator),
                  static_cast<int>(message_size));
  result = std::move(raw_data);
  return result;
}

std::optional<std::uint8_t>
GetPackectMessageType(PacketBufferIterator packet_message_iterator) {
  std::optional<std::uint8_t> result;
  std::uint8_t message_type;
  std::memcpy(&message_type, packet_message_iterator, MESSAGE_TYPE_SIZE);
  result = message_type;
}

} // namespace utils
} // namespace agents
