#ifndef __AGENTS_MIDDLEWARE_DATA_TYPES_H_
#define __AGENTS_MIDDLEWARE_DATA_TYPES_H_
#include "devices_proxys/devices_proxy_mananger.h"
#include <memory>
namespace agents {
  namespace middleware {
    namespace commnands {

      enum class State : std::uint8_t {
        Executed,
        Failed,
        Waiting,
        CommandNotFound,
        CommandNotExecutedDeviceNotFound
      };

      enum class Id : std::uint32_t {
        StopDevice = 0,                // Stop Device ID=0
        RequestCurrentStatus = 1,      // Request Current Status ID=1
        RequestStatusOfAllDevices = 2, // Request Status of All Devices ID=2
        ResetDeviceCommand = 3,        // Reset Device
        StartDevice = 4,               // Start Device
        StartAllDevices = 5            // Start All Devices
      };

      template <typename DerivedCommand>
      struct BaseCommandPattern : DerivedCommand {

        State Execute(std::uint32_t device_id) {
          static_cast<&DerivedCommand>(*this)->Interface(device_id);
        }
      };

      // Internal Command Definition
      struct StopDevice : BaseCommandPattern<StopDeviceCommand> {
        explicit(std::shared_ptr<DeviceManager> device_manager) :
            device_manager_(device_manager) {}

        State Interface(std::uint32_t device_id) {
          const State status = device_manager_->StopDevice(device_id);
          return status;
        }

        std::shared_ptr<DeviceManager> device_manager_;
        const Id command_id_ = Ids::StopDevice;
      };

      struct RequestCurrentStatus : BaseCommandPattern<StopDeviceCommand> {
        explicit(std::shared_ptr<DeviceManager> device_manager) :
            device_manager_(device_manager) {}

        State Interface(std::uint32_t device_id) {
          const State status = device_manager_->RequestCurrentStatus(device_id);
          return status;
        }

        std::shared_ptr<DeviceManager> device_manager_;
        const Id command_id_ = Ids::RequestCurrentStatus;
      };
      //
      struct RequestStatusOfAllDevices : BaseCommandPattern<StopDeviceCommand> {
        explicit(std::shared_ptr<DeviceManager> device_manager) :
            device_manager_(device_manager) {}

        State Interface(std::uint32_t) {
          const State status = device_manager_->RequestStatusOfAllDevices();
          return status;
        }
        std::shared_ptr<DeviceManager> device_manager_;
        const Id command_id_ = Ids::RequestStatusOfAllDevices;
      };
      //
      struct ResetDevice : BaseCommandPattern<StopDeviceCommand> {
        explicit(std::shared_ptr<DeviceManager> device_manager) :
            device_manager_(device_manager) {}

        State Interface(std::uint32_t device_id) {
          const State status = device_manager_->ResetDevice(device_id);
          return status;
        }

        std::shared_ptr<DeviceManager> device_manager_;
        const Id command_id_ = Ids::ResetDeviceCommand;
      };
      //
      struct StartDevice : BaseCommandPattern<StopDeviceCommand> {
        explicit(std::shared_ptr<DeviceManager> device_manager) :
            device_manager_(device_manager), {}

        State Interface(std::uint32_t device_id) {
          const State status = device_manager_->StartDevice(device_id);
          return status;
        }

        std::shared_ptr<DeviceManager> device_manager_;
        const Id command_id_ = Ids::StartDevice;
      };

      struct StartAllDevices : BaseCommandPattern<StopDeviceCommand> {
        explicit(std::shared_ptr<DeviceManager> device_manager) :
            device_manager_(device_manager) {}

        State Interface(std::uint32_t) {
          const State status = device_manager_->StartAllDevices();
          return status;
        }
        std::shared_ptr<DeviceManager> device_manager_;
        const Id command_id_ = Ids::StartAllDevices;
      };

    } // namespace commnands

  } // namespace middleware
} // namespace agents
#endif
