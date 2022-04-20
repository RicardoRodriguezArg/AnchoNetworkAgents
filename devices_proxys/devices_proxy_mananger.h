#ifndef __AGENTS_MIDDLEWARE_DEVICES_PROXYS_MANAGER_H_
#define __AGENTS_MIDDLEWARE_DEVICES_PROXYS_MANAGER_H_
#include "commands/definitions.h"
#include "devices_proxy.h"
#include <algorithm>
#include <vector>

// TODO: change to amp vector
namespace agents {
  namespace middleware {
    namespace proxys {
      struct ProxyManager {
        using DeviceProxyType = agents::middleware::proxys::DeviceProxy;
        void BuildProxyDevicesFromInputList(const std::vector<std::uint32_t> proxy_id_list,
                                            std::function<bool(const std::string&)> command_dispatcher_callback,
                                            std::shared_ptr<CommandMessageDictionary> message_command_dict) {
          proxy_list_.reserve(proxy_id_list.size());
          std::transform(proxy_id_list.cbegin(), proxy_id_list.cend(), std::back_inserter(proxy_list_),
                         [&command_dispatcher_callback, &message_command_dict](const auto proxy_id) {
                           const auto device = DeviceProxy{command_dispatcher_callback, message_command_dict};
                           const auto value = std::make_pair(proxy_id, device);
                           return value;
                         });
        }

        // TODO: change to proper error propagation and handling
        std::int32_t RequestCurrentStatus(std::uint32_t device_id) {
          // TODO: Specify formal protocol in a Jira Document
          // https://galileo-belly.atlassian.net/browse/EZI-38
          // TODO: change to proper error propagation and handling
          std::int32_t command_execution_state{-1};
          auto device = GetDeviceById(device_id);
          if (device.has_value()) {
            command_execution_state =
              //(*device).ExecuteCommand(static_cast<std::uint32_t>(
              //  agents::middleware::commnands::Id::RequestCurrentStatus));
              (*device).ExecuteCommand(1);
            // Here we should notify to Events/Telemtry Manager to update device
            // status/info from this commands also if the commands was
            // requesting ACK
          }
          return command_execution_state;
        }

        std::optional<DeviceProxy> GetDeviceById(std::uint32_t device_id) {
          std::optional<DeviceProxy> result{};
          const auto iterator =
            std::find_if(proxy_list_.cbegin(), proxy_list_.cend(), [&device_id](const auto& tuple_proxy_info) {
              return std::get<std::uint32_t>(tuple_proxy_info) == device_id;
            });
          if (iterator != std::end(proxy_list_)) {
            result = std::get<DeviceProxyType>((*iterator));
          }

          return result;
        }

        std::vector<std::tuple<std::uint32_t, DeviceProxy>> proxy_list_ = {};
      };
    } // namespace proxys
  }   // namespace middleware
} // namespace agents
#endif
