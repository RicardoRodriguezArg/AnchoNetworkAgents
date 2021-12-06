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

std::optional<std::string> UnpackMessage(const std::string_view input_message);

/**
 * @brief      Pack Input String view into our protocol
 *
 * @param[in]  input_message  The input message
 *
 * @return     { packet message (4 bytes) + size of packet message }
 */
std::optional<std::string> PackMessageToString(
    const std::string_view input_message);

/**
 * @brief      Gets the packect message size.
 *
 * @param[in]  packet_message  The packet message
 *
 * @return     The packect message size.
 */
std::optional<std::uint32_t> GetPackectMessageSize(
    std::string_view packet_message);

}  // namespace utils

}  // namespace agents
#endif
