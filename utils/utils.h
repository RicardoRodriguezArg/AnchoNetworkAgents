#ifndef __AGENT_UTILS_H_
#define __AGENT_UTILS_H_

#include "commons/commons.h"
#include <array>
#include <cstring>
#include <limits>
#include <optional>
#include <string_view>

namespace agents {
  namespace utils {

    static constexpr std::uint8_t MESSAGE_SIZE_DEFAULT = 4U;
    static constexpr std::uint32_t MAX_BUFFER_SIZE = 1024U;
    static constexpr std::uint8_t MESSAGE_TYPE_SIZE = 4U;

    using ConstPacketBufferIterator = char const*;
    using PacketBufferIterator = char*;
    using PacketBuffer = std::array<char, MAX_BUFFER_SIZE>;
    using MessageSize = std::uint8_t;
    /**
     * TODO: aricardorodriguez@hotmail.com: Need to improve this interface, as
     * the tests has a highly dependence on the input iterator so, the method
     * should:
     * 1.- Validate the iterator
     * 2.- Do not allow arithmetic validation
     * on the input interface
     */

    /**
     * @brief      Encode input message with define protocol
     *             First Part - 4 Bytes enconde the size of the whole message
     *             Second Part - 4 Byte for message type
     *
     * @param[in]  input_message            The input message
     * @param[in]  packet_message_iterator  The packet message iterator
     * @param[in]  message_type             The message type
     *
     * @return     Return true if could enconded, false otherwise
     */
    bool PackMessageToString(std::string_view input_message, PacketBufferIterator packet_message_iterator,
                             common::MessageType message_type);

    /**
     * @brief      Gets the packect message size.
     *
     * @param[in]  packet_message iterator to Begining of the encoded message
     *
     * @return     The packect message size.
     */
    std::optional<std::uint32_t> GetPackectMessageSize(PacketBufferIterator packet_message_iterator);

    /**
     * @brief      Gets the packect message data.
     *
     * @param[in]  packet_message_iterator  The packet message iterator
     *
     * @return     The packect message data.
     */
    std::optional<std::string> GetPackectMessageData(PacketBufferIterator packet_message_iterator,
                                                     MessageSize raw_message_size);

    /**
     * @brief      Gets the message type.
     *
     * @param[in]  packet_message_iterator  The packet message iterator
     *
     * @return     The Optional message type.
     */
    std::optional<std::uint8_t> GetPackectMessageType(PacketBufferIterator packet_message_iterator);

  } // namespace utils

} // namespace agents
#endif
