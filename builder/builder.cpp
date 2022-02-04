#include "middleware_factory.h"
#include <stdexcept>

namespace agents {
  namespace middleware {
    {
      namespace {
        ::agent_interface_Header CreateMessageHeader() {
          ::agent_interface_Header header_message{};
          header_message.source_agent_id =
            static_cast<std::uint32_t>(agents::common::DeviceId::MainUdpServer);
          header_message.timestamp = {0.0F};
        }

        ::agent_interface_CommandWithArguments CreateNanoCommandFromId(
          const commnands::Id nano_command_id) {
          ::agent_interface_CommandWithArguments nano_command;
          switch (commnands::Id) {
          case commnands::Id::StopDevice: {
            nano_command.id =
              static_cast<std::uint32_t>(commnands::Id::StopDevice);
            nano_command.header_message = CreateMessageHeader();

          } break;
          case commnands::Id::RequestCurrentStatus: {
            nano_command.id =
              static_cast<std::uint32_t>(commnands::Id::RequestCurrentStatus);
            nano_command.header_message = CreateMessageHeader();

          } break;
          case commnands::Id::RequestStatusOfAllDevices: {
            nano_command.id = static_cast<std::uint32_t>(
              commnands::Id::RequestStatusOfAllDevices);
            nano_command.header_message = CreateMessageHeader();

          } break;
          case commnands::Id::ResetDeviceCommand: {
            nano_command.id =
              static_cast<std::uint32_t>(commnands::Id::ResetDeviceCommand);
            nano_command.header_message = CreateMessageHeader();
          } break;
          case commnands::Id::StartDevice: {
            nano_command.id =
              static_cast<std::uint32_t>(commnands::Id::StartDevice);
            nano_command.header_message = CreateMessageHeader();
          } break;
          case commnands::Id::StartAllDevices: {
            nano_command.id =
              static_cast<std::uint32_t>(commnands::Id::StartAllDevices);
            nano_command.header_message = CreateMessageHeader();
          } break;

          default: {
            throw std::runtime_error(
              {"Incorrect nano command id, failing at building time "});
          } break;
          }
          return nano_command;
        }

      } // namespace
      std::vector<std::uint8_t> GetAllCommandsIDsFromDataBase() {
        // TODO: Temporary workaround until DB is defined
        std::vector<std::uint8_t> commands_id{0U, 1U, 2U, 3U, 4U, 5U};
        return commands_id;
      }

      CommandMessageDict CreateAllNanoCommands(
        const std::vector<std::uint8_t>& commands_ids_input_list) {
        std::array<::agent_interface_CommandWithArguments, MAX_MESSAGE_COUNT>
          array_from_factory{};
        std::transform(commands_ids_input_list.cbegin(),
                       commands_ids_input_list.cend(),
                       std::back_inserter(array_from_factory),
                       [](const internal_commnad_id) {
                         return CreateNanoCommandFromId(internal_commnad_id);
                       })

          CommandMessageDict result{std::move(array_from_factory)};
        return result;
      }

      std::vector<std::uint32_t> LoadDevicesIdsFromConfig() { return {0U}; }

      proxys::ProxyManager CreateProxyManagerFromConfig(
        const std::vector<std::uint32_t>& device_proxy_list) {
        proxys::ProxyManager proxy_manager;
        return proxy_manager;
      }

      InternalCommandsHandler CreateInternalCommandsHandlers(
        const std::shared_ptr<DeviceManager>& device_manager_ptr) {
        commnands::StartAllDevices start_all_devices{device_manager_ptr};
        commnands::StopDevice stop_device{device_manager_ptr};
        commnands::RequestCurrentStatus request_current_status{
          device_manager_ptr};
        commnands::RequestStatusOfAllDevices request_status_all_devices{
          device_manager_ptr};
        commnands::ResetDevice reset_device{device_manager_ptr};
        commnands::StartDevice start_device{device_manager_ptr};

        return std::make_tuple(start_all_devices, start_device, reset_device,
                               request_status_all_devices,
                               request_current_status, stop_device);
      }

    } // namespace middleware
  }   // namespace middleware
