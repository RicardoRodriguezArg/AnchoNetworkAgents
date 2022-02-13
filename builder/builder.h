#ifndef __AGENTS_MIDDLEWARE_MIDDLEWARE_FACTORY_H_
#define __AGENTS_MIDDLEWARE_MIDDLEWARE_FACTORY_H_

#include "commands/commands.h"
#include "interface/message_interface_idl.pb.h"
// devices proxys
#include "commons/commons.h"
#include "data_processors/data_messages.h"
#include "devices_proxys/devices_proxy_mananger.h"
#include "eth_layer/udp_server.h"
// Server
#include "communication/server.h"
#include "communication/server_options.h"

#include <vector>

namespace agents {
  namespace middleware {
    namespace builders {

      using namespace agents::middleware::commands;
      using InternalCommandsHandler = std::tuple<StopDevice, StartAllDevices, StartDevice, ResetDevice,
                                                 RequestStatusOfAllDevices, RequestCurrentStatus>;
      using InternalEventHandler = std::tuple<std::uint32_t>;
      using CommandMessageDict = MessageDictionary<::agent_interface_CommandWithArguments>;
      using ServerOptionsType = agents::middleware::options::ServerConfiguration;
      using EventMessageDict = MessageDictionary<::agent_interface_Event>;

      using ProxyManagerType = agents::middleware::proxys::ProxyManager;
      // Commands
      std::vector<std::uint8_t> GetAllCommandsIDsFromDataBase();                                          // Done
      CommandMessageDict CreateAllNanoCommands(const std::vector<std::uint8_t>& commands_ids_input_list); // Done

      // Device Proxy List
      std::vector<std::uint32_t> LoadDevicesIdsFromConfig(); // Done
      ProxyManagerType CreateProxyManagerFromConfig();       // Done

      InternalCommandsHandler CreateAllInternalCommandsHandlers(
        const std::shared_ptr<ProxyManagerType>& device_manager_ptr); // Done
      handlers::MessageHandlerManger BuildMessageHandler();
      handlers::MessageHandlerManger ConfigureMessageHandler(handlers::MessageHandlerManger message_handler);
      ServerOptionsType LoadServerOptions();
      // Configure Server
      Server CreateAndConfigureMainServerFromConfig(const handlers::MessageHandlerManger& message_handler,
                                                    const ServerOptionsType& server_options);
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

    } // namespace builders

  } // namespace middleware
} // namespace agents
#endif
