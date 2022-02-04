#ifndef __AGENTS_MIDDLEWARE_MIDDLEWARE_FACTORY_H_
#define __AGENTS_MIDDLEWARE_MIDDLEWARE_FACTORY_H_

#include "commands/commands.h"
#include "interface/message_interface_idl.pb.h"
// devices proxys
#include "common/commons.h"
#include "communication/server.h"
#include "data_processors/data_messages.h"
#include "factory/devices_proxy_mananger.h"
// Server
#include "communication/server.h"
#include "communication/server_options.h"

#include <vector>

namespace agents {
  namespace middleware {
    namespace builders {

      using agents::middleware::commands;
      using InternalCommandsHandler =
        std::tuple<StartAllDevices, StartDevice, ResetDevice,
                   RequestStatusOfAllDevices, RequestCurrentStatus, StopDevice>;
      using InternalEventHandler = std::tuple<std::uint32_t>;
      using CommandMessageDict =
        MessageDictionary<::agent_interface_CommandWithArguments>;
      using EventMessageDict = MessageDictionary<::agent_interface_Event>;
      // Commands
      std::vector<std::uint8_t> GetAllCommandsIDsFromDataBase(); // Done
      CommandMessageDict CreateAllNanoCommands(
        const std::vector<std::uint8_t>& commands_ids_input_list); // Done

      // Device Proxy List
      std::vector<std::uint32_t> LoadDevicesIdsFromConfig(); // Done
      proxys::ProxyManager CreateProxyManagerFromConfig(
        const std::vector<std::uint32_t>& device_proxy_list); // Done
      // Proxy Command Handler
      InternalCommandsHandler CreateInternalCommandsHandlers(
        std::shared_ptr<DeviceManager>& device_manager_ptr); // Done
      // Events
      /*std::vector<std::uint32_t> LoadEventsIdsFromConfig();
      EventMessageDict CreateNanoEventsFromConfig(
        const std::vector<std::uint32_t>&);
      InternalEventHandler CreateInternalEventFromConfig(
        const std::vector<std::uint32_t>&);

      // Data-Telemetry
      std::vector<std::uint32_t> LoadDataTelemetryIdsFromConfig();
      EventMessageDict CreateNanoTelemetryFromConfig(
        const std::vector<std::uint32_t>&);
      InternalEventHandler CreateInternalDataTelemetryFromConfig(
        const std::vector<std::uint32_t>&);
        */
      // Message Handler
      handlers::MessageHandlerManger BuildMessageHandler();
      options::ServerOptions LoadServerOptions();
      // Configure Server
      Server CreateAndConfigureMainServerFromConfig(
        const options::ServerOptions& server_options);
    } // namespace builders

  } // namespace middleware
} // namespace agents
#endif
