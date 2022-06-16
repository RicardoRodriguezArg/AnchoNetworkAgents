#ifndef __AGENTS_MIDDLEWARE_MIDDLEWARE_MESSAGE_HANDLER_BUILDER_H_
#define __AGENTS_MIDDLEWARE_MIDDLEWARE_MESSAGE_HANDLER_BUILDER_H_
#include "builder/builder.h"
#include "utils/serializer.h"
#include <glog/logging.h>

namespace agents {
  namespace middleware {
    namespace builders {
      class MessageHandlers {
      public:
        static handlers::MessageHandlerManger Build() {
          handlers::MessageHandlerManger message_handler{};
          std::function<void(const std::string&)> nano_command_handler = [](const std::string& raw_data) {
            LOG(INFO) << "Deserealizing Nano Command Handler";
            agents::utils::Serializer serializer;
            const auto result = serializer.DeSerializeCommandFromString(raw_data);
            if (result.has_value()) {
              const auto command = result.value();

              LOG(INFO) << "Command id: " << command.id;
              LOG(INFO) << "Command Number of Arguments: " << command.number_arg_count;
            }
          };

          std::function<void(const std::string&)> proto_command_handler = [](const std::string& raw_data) {
            LOG(INFO) << "Deserealizing Proto Command Handler";
            agent_interface::CommandWithArguments command_with_arguments{};
            if (command_with_arguments.ParseFromString(raw_data)) {
              command_with_arguments.PrintDebugString();
              LOG(INFO) << "Command Proto Id: " << command_with_arguments.id();
              LOG(INFO) << "Command header Id: " << command_with_arguments.header().message_id();
            }
          };
          message_handler.RegisterMessageHandler(agents::common::MessageType::COMAND_NANO, nano_command_handler);
          message_handler.RegisterMessageHandler(agents::common::MessageType::COMMAND_PROTO, proto_command_handler);
          return message_handler;
        }

      private:
      }; // namespace builders
    }    // namespace builders
  }      // namespace middleware
} // namespace agents
#endif
