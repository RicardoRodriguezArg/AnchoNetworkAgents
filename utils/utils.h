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
using ConstPacketBufferIterator = std::uint8_t const *;
using PacketBufferIterator = std::uint8_t *;
using PacketBuffer = std::array<std::uint8_t, MAX_BUFFER_SIZE>;

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
 * @param[in]  input_message  The input message
 *
 * @return     Encoded message with size of the message at first 4 bytes
 */
std::optional<PacketBuffer> PackMessageToString(
    const std::string_view input_message);

/**
 * @brief      Gets the packect message size.
 *
 * @param[in]  packet_message iterator to Begining of the encoded message
 *
 * @return     The packect message size.
 */
std::optional<std::uint32_t> GetPackectMessageSize(
    PacketBufferIterator packet_message_iterator);

}  // namespace utils

}  // namespace agents
#endif
