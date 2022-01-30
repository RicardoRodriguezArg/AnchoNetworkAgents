#ifndef __AGENTS_MIDDLEWARE_DEVICES_PROXYS_H_
#define __AGENTS_MIDDLEWARE_DEVICES_PROXYS_H_
#include "data_processors/data_processors_commons.h"
#include "data_sender/command_dispatcher.h"
#include "data_types/commands.h"
#include <functional>
#include <memory>

namespace agents {
  namespace middleware {
    namespace proxys {
      enum class State : std::uint8_t {
        INIT,
        NON_INIT,
        NON_CONNECTED,
        CONNECTED,
        LAGGING
      };

      struct DeviceProxy {
        explicit DeviceProxy(
          std::function<bool(const std::string&)> command_dispatcher_callback,
          std::shared_ptr<agents::middleware::CommandMessageDict>
            message_command_dict) :
            command_dispatcher_callback_(command_dispatcher_callback),
            message_command_dict_(message_command_dict) {}

        // TODO:: Add Argument parameter to increase functionality
        commnands::State ExecuteCommand(std::uint32_t command_id_to_execute) {
          commnands::State result = commnands::State::CommandNotFound;

          const auto nano_commnand_opt =
            message_command_dict_->GetMessageFromDictionary(
              command_id_to_execute);
          if (nano_commnand_opt) {
            // TODO:Change to use string view and avoid copy
            const auto encoded_command =
              data_encoder_.EncodeCommand(*nano_commnand_opt);
            if (encoded_command.empty()) {
              command_dispatcher_callback_(encoded_command);
              last_command_executed_ = command_id_to_execute;
            }
          }
          return result;
        }

        void SetProxyState(State state) {
          previous_proxy_state_ = current_proxy_state_;
          current_proxy_state_ = state;
        }

        std::optional<std::uint32_t> last_command_executed_;
        State current_proxy_state_ = State::NON_CONNECTED;
        State previous_proxy_state_ = State::NON_CONNECTED;
        std::function<bool(const std::string&)> command_dispatcher_callback_;
        std::shared_ptr<agents::middleware::CommandMessageDict>
          message_command_dict_;
        middleware::DataDecoder data_encoder_;
      };
    } // namespace proxys

  } // namespace middleware
} // namespace agents

#endif
