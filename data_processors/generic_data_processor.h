#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_GENERIC_DATA_PROCESSOR_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_GENERIC_DATA_PROCESSOR_H_

#include "data_processors/data_messages.h"
#include "data_processors/data_processor_commons.h"

namespace agents {
  namespace middleware {
    template <typename NanoMessageType, typename AgentMessage>
    struct CommandsProcessor {

      explicit CommandsProcessor(
        const MessageDictionary<AgentMessage>& agent_message_dictionay) :
          agent_message_dictionay_(agent_message_dictionay) {}

      void Process(const std::string& raw_message) {
        if (!raw_message.empty()) {
          const auto decoded_command =
            data_decoder_.DecodeToCommand(raw_message);
          ProcessTranformedMessage(decoded_command);
        }
      }

    private:
      void ProcessTranformedMessage(const NanoMessageType& nano_message_type) {
        const auto command_to_execute =
          agent_message_dictionay_.GetMessageFromDictionary(
            nano_message_type.id);
        if (command_to_execute.has_value()) {
          (*command_to_execute).execute();
        }
      }

      DataDecoder data_decoder_;
      MessageDictionary<AgentMessage> agent_message_dictionay_;
      ;
    };
  } // namespace middleware
} // namespace agents
#endif