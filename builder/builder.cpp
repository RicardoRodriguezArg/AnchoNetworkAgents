#include "builder.h"
#include <glog/logging.h>
#include <stdexcept>

namespace agents {
  namespace middleware {

    namespace {
      ::agent_interface_Header CreateMessageHeader() {
        ::agent_interface_Header header_message{};
        header_message.source_agent_id = static_cast<std::uint32_t>(agents::common::DeviceId::MainUdpServer);
        header_message.timestamp = {0.0F};
        return header_message;
      }

      ::agent_interface_CommandWithArguments CreateNanoCommandFromId(
        const agents::middleware::commands::Id nano_command_id) {
        LOG(INFO) << "Creating Nano Command number:  " << static_cast<std::int32_t>(nano_command_id);
        using namespace agents::middleware::commands;
        ::agent_interface_CommandWithArguments nano_command;
        switch (nano_command_id) {
        case Id::kStopDevice: {
          LOG(INFO) << "Creating Nano Stop Command";
          nano_command.id = static_cast<std::uint32_t>(Id::kStopDevice);
          nano_command.header = CreateMessageHeader();

        } break;
        case Id::kRequestCurrentStatus: {
          LOG(INFO) << "Creating Nano Request Current Status";
          nano_command.id = static_cast<std::uint32_t>(Id::kRequestCurrentStatus);
          nano_command.header = CreateMessageHeader();

        } break;
        case Id::kRequestStatusOfAllDevices: {
          LOG(INFO) << "Creating Nano Request status on All Devices";
          nano_command.id = static_cast<std::uint32_t>(Id::kRequestStatusOfAllDevices);
          nano_command.header = CreateMessageHeader();

        } break;
        case Id::kResetDeviceCommand: {
          LOG(INFO) << "Creating Nano Request Request on Device";
          nano_command.id = static_cast<std::uint32_t>(Id::kResetDeviceCommand);
          nano_command.header = CreateMessageHeader();
        } break;
        case Id::kStartDevice: {
          LOG(INFO) << "Creating Nano Start Device";
          nano_command.id = static_cast<std::uint32_t>(Id::kStartDevice);
          nano_command.header = CreateMessageHeader();
        } break;
        case Id::kStartAllDevices: {
          LOG(INFO) << "Creating Start All Devices";
          nano_command.id = static_cast<std::uint32_t>(Id::kStartAllDevices);
          nano_command.header = CreateMessageHeader();
        } break;

        default: {
          throw std::runtime_error({"Incorrect nano command id, failing at building time "});
        } break;
        }
        return nano_command;
      }

    } // namespace

    namespace builders {

      std::vector<std::uint8_t> GetAllCommandsIDsFromDataBase() {
        // TODO: Temporary workaround until DB is defined
        std::vector<std::uint8_t> commands_id{0U, 1U, 2U, 3U, 4U, 5U};
        return commands_id;
      }

      CommandMessageDict CreateAllNanoCommands(const std::vector<std::uint8_t>& commands_ids_input_list) {
        std::array<::agent_interface_CommandWithArguments, agents::common::MAX_MESSAGE_COUNT> array_from_factory{};
        std::transform(
          commands_ids_input_list.begin(), commands_ids_input_list.end(), array_from_factory.begin(),
          [](const auto& internal_commnad_id) {
            return CreateNanoCommandFromId(static_cast<agents::middleware::commands::Id>(internal_commnad_id));
          });

        CommandMessageDict result{std::move(array_from_factory)};
        return result;
      }

      std::vector<std::uint32_t> LoadDevicesIdsFromConfig() { return {0U}; }

      proxys::ProxyManager CreateProxyManagerFromConfig() {
        proxys::ProxyManager proxy_manager;
        return proxy_manager;
      }

      InternalCommandsHandler CreateAllInternalCommandsHandlers(
        const std::shared_ptr<ProxyManagerType>& device_manager_ptr) {
        commands::StartAllDevices start_all_devices{device_manager_ptr};
        commands::StopDevice stop_device{device_manager_ptr};
        commands::RequestCurrentStatus request_current_status{device_manager_ptr};
        commands::RequestStatusOfAllDevices request_status_all_devices{device_manager_ptr};
        commands::ResetDevice reset_device{device_manager_ptr};
        commands::StartDevice start_device{device_manager_ptr};

        return std::make_tuple(stop_device, start_all_devices, start_device, reset_device, request_status_all_devices,
                               request_current_status);
      }

      handlers::MessageHandlerManger BuildMessageHandler() {
        handlers::MessageHandlerManger message_handler{};
        return message_handler;
      }

      handlers::MessageHandlerManger ConfigureMessageHandler(handlers::MessageHandlerManger message_handler) {
        return message_handler;
      }

      ServerOptionsType LoadServerOptions() { return {}; }

      Server CreateAndConfigureMainServerFromConfig(const handlers::MessageHandlerManger& message_handler,
                                                    const ServerOptionsType& server_options) {
        Server server{message_handler, server_options.server_port_};
        return server;
      }

    } // namespace builders

  } // namespace middleware
} // namespace agents
