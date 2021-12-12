#ifndef __AGENT_UTILS_H_
#define __AGENT_UTILS_H_

#include <array>
#include <cstring>
#include <limits>
#include <optional>
#include <string_view>

namespace agents {
namespace utils {

static constexpr std::uint8_t MESSAGE_SIZE_DEFAULT = 4U;
static constexpr std::uint32_t MAX_BUFFER_SIZE = 512U;
using ConstPacketBufferIterator = char const *;
using PacketBufferIterator = char *;
using PacketBuffer = std::array<char, MAX_BUFFER_SIZE>;
using MessageSize = std::uint8_t;

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

std::optional<std::string> UnpackMessage(const std::string_view input_message);

/**
 * @brief      Encode input message with define protocol
 *             First 4 Bytes enconde the size of the whole message
 *
 * @param[in]  input_message            The input message
 * @param[in]  packet_message_iterator  The packet message iterator
 *
 * @return     Return true if could enconded, false otherwise
 */
bool PackMessageToString(const std::string_view input_message,
                         PacketBufferIterator packet_message_iterator);

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

}  // namespace utils

}  // namespace agents
#endif
