#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMANDS_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_COMMANDS_H_

#include "data_processors/data_processor_commons.h"

namespace agents {
namespace middleware {
struct CommandsProcessor {
  void Process(const std::string &raw_message) {
    if (!raw_message.empty()) {
      const auto decoded_command = data_decoder_.DecodeToCommand(raw_message);
      ProcessCommandWithArguments(decoded_command);
    }
  }

private:
  void ProcessCommandWithArguments(
      const agent_interface_CommandWithArguments &command_with_argument) {
    switch (command_with_argument.id) {
    case 1: {

    } break default : {
    }
      break;
    }
  }
  DataDecoder data_decoder_;
  ;
};
} // namespace middleware
} // namespace agents
#endif