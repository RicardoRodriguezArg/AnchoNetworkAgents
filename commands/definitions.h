#ifndef __AGENTS_MIDDLEWARE_COMMANDS_COMMANDS_DEFINITIONS_H__
#define __AGENTS_MIDDLEWARE_COMMANDS_COMMANDS_DEFINITIONS_H__
#include <cstdint>

namespace agents {
  namespace middleware {
    namespace commands {

      enum class State : std::uint8_t {
        kExecuted,
        kFailed,
        kWaiting,
        kCommandNotFound,
        kDeviceNotFound,
      };

      enum class Id : std::uint32_t {
        kStopDevice = 0,                // Stop Device ID=0
        kRequestCurrentStatus = 1,      // Request Current Status ID=1
        kRequestStatusOfAllDevices = 2, // Request Status of All Devices ID=2
        kResetDeviceCommand = 3,        // Reset Device
        kStartDevice = 4,               // Start Device
        kStartAllDevices = 5,           // Start All Devices
      };
    } // namespace commands
  }   // namespace middleware
} // namespace agents
#endif
