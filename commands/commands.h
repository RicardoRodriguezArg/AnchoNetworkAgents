#ifndef __AGENTS_MIDDLEWARE_COMMANDS_COMMANDS_H_
#define __AGENTS_MIDDLEWARE_COMMANDS_COMMANDS_H_
#include "definitions.h"
#include "devices_proxys/devices_proxy_mananger.h"
#include <memory>

namespace agents {
  namespace middleware {
    namespace commands {

      template <typename DerivedCommand, int>
      struct BaseCommandPattern : DerivedCommand {

        State Execute(std::uint32_t device_id) {
          DerivedCommand& derived = static_cast<DerivedCommand&>(*this);
          // const auto result = derived.Execute(device_id);
          return State::kCommandNotFound;
        }
      };

      // Internal Command Definition
      using ProxyManagerType = agents::middleware::proxys::ProxyManager;

      struct StopDevice {
        explicit StopDevice(std::shared_ptr<ProxyManagerType> device_manager) : device_manager_(device_manager) {}

        State Execute(std::uint32_t device_id) {
          State command_execution_result{State::kDeviceNotFound};
          auto device_opt = device_manager_->GetDeviceById(device_id);
          if (device_opt.has_value()) {
            auto device_proxy = *device_opt;
            const auto command_execution = device_proxy.ExecuteCommand(static_cast<std::uint32_t>(Id::kStopDevice));
            // TODO: Add ACK component, as we always we want to receive ACK from
            // device
            command_execution_result = (command_execution > 0) ? State::kExecuted : State::kFailed;
          }
          return command_execution_result;
        }

        const std::shared_ptr<ProxyManagerType> device_manager_;
      };

      struct RequestCurrentStatus {
        explicit RequestCurrentStatus(std::shared_ptr<ProxyManagerType> device_manager) :
          device_manager_(device_manager) {}

        State Execute(std::uint32_t device_id) { return State::kCommandNotFound; }
        const std::shared_ptr<ProxyManagerType> device_manager_;
      };

      //
      struct RequestStatusOfAllDevices {
        explicit RequestStatusOfAllDevices(std::shared_ptr<ProxyManagerType> device_manager) :
          device_manager_(device_manager) {}

        State Execute(std::uint32_t device_id) { return State::kCommandNotFound; }
        const std::shared_ptr<ProxyManagerType> device_manager_;
      };

      //
      struct ResetDevice {
        explicit ResetDevice(std::shared_ptr<ProxyManagerType> device_manager) : device_manager_(device_manager) {}

        State Execute(std::uint32_t device_id) { return State::kCommandNotFound; }

        const std::shared_ptr<ProxyManagerType> device_manager_;
      };

      //
      struct StartDevice {
        explicit StartDevice(std::shared_ptr<ProxyManagerType> device_manager) : device_manager_(device_manager) {}

        State Execute(std::uint32_t) { return State::kCommandNotFound; }

        const std::shared_ptr<ProxyManagerType> device_manager_;
      }; // namespace commands

      struct StartAllDevices {
        explicit StartAllDevices(std::shared_ptr<ProxyManagerType> device_manager) : device_manager_(device_manager) {}

        State Execute(std::uint32_t) { return State::kCommandNotFound; }
        const std::shared_ptr<ProxyManagerType> device_manager_;
      };

    } // namespace commands

  } // namespace middleware
} // namespace agents
#endif
