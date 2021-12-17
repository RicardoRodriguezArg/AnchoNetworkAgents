#ifndef __AGENT_UTILS_H_
#define __AGENT_UTILS_H_

#include <array>
#include <cstring>
#include <limits>
#include <optional>
#include <string_view>
#include "common/commons.h"

namespace agents {
namespace utils {

static constexpr std::uint8_t MESSAGE_SIZE_DEFAULT = 4U;
static constexpr std::uint32_t MAX_BUFFER_SIZE = 512U;
static constexpr std::uint8_t MESSAGE_TYPE_SIZE = 4U;

using ConstPacketBufferIterator = char const *;
using PacketBufferIterator = char *;
using PacketBuffer = std::array<char, MAX_BUFFER_SIZE>;
using MessageSize = std::uint8_t;

/**
 * @brief      Encode input message with define protocol
 *             First 4 Bytes enconde the size of the whole message
 *             Second 1 Byte for message type
 *
 * @param[in]  input_message            The input message
 * @param[in]  packet_message_iterator  The packet message iterator
 * @param[in]  message_type             The message type
 *
 * @return     Return true if could enconded, false otherwise
 */
bool PackMessageToString(const std::string_view input_message,
                         PacketBufferIterator packet_message_iterator,
                         common::MessageType message_type);

/**
 * @brief      Gets the packect message size.
 *
 * @param[in]  packet_message iterator to Begining of the encoded message
 *
 * @return     The packect message size.
 */
std::optional<std::uint32_t> GetPackectMessageSize(
    PacketBufferIterator packet_message_iterator);

/**
 * @brief      Gets the packect message data.
 *
 * @param[in]  packet_message_iterator  The packet message iterator
 *
 * @return     The packect message data.
 */
std::optional<std::string> GetPackectMessageData(
    PacketBufferIterator packet_message_iterator, MessageSize raw_message_size);

/**
 * @brief      Gets the message type.
 *
 * @param[in]  packet_message_iterator  The packet message iterator
 *
 * @return     The message type.
 */
std::optional<std::uint8_t> GetMessageType(
    PacketBufferIterator packet_message_iterator);

}  // namespace utils

}  // namespace agents
#endif
