#ifndef __AGENTS_MIDDLEWARE_DEVICES_PROXYS_MANAGER_H_
#define __AGENTS_MIDDLEWARE_DEVICES_PROXYS_MANAGER_H_
#include "devices_proxy.h"
#include <algorithm>
#include <vector>

// TODO: change to amp vector
namespace agents {
  namespace middleware {
    namespace proxys {
      struct ProxyManager {

        void BuildProxyDevicesFromInputList(
          const std::vector<std::uint32_t> proxy_id_list,
          std::function<bool(const std::string&)> command_dispatcher_callback,
          std::shared_ptr<agents::middleware::CommandMessageDict>
            message_command_dict) {
          proxy_list_.reserve(proxy_id_list.count());
          std::transform(proxy_id_list.cbegin(), proxy_id_list.cend(),
                         std::back_inserter(proxy_list_),
                         [&command_dispatcher_callback,
                          &message_command_dict](const auto proxy_id) {
                           const auto device = DeviceProxy{
                             command_dispatcher_callback, message_command_dict};
                           const auto value = std::make_pair(proxy_id, device);
                           return value;
                         })
        }

        commnands::State RequestCurrentStatus(std::uint32_t device_id) {
          // TODO: Specify formal protocol in a Jira Document
          // https://galileo-belly.atlassian.net/browse/EZI-38
          commnands::State command_execution_state{
            commnands::State::CommandNotExecutedDeviceNotFound};
          const auto device = GetDeviceById(device_id);
          if (device != proxy_list_.end()) {
            command_execution_state = device->ExecuteCommand(
              static_cast<std::uint32_t>(commnands::Id::RequestCurrentStatus));
            // Here we should notify to Events/Telemtry Manager to update device
            // status/info from this commands also if the commands was
            // requesting ACK
          }
          return result;
        }

        std::vector<std::tuple<std::uint32_t, DeviceProxy>>::iterator
        GetDeviceById(std::uint32_t device_id) {
          const auto iterator = std::find_if(
            proxy_list_.cbegin(), proxy_list_.cend(),
            [&device_id](const auto& tuple_proxy_info) {
              return std::get<std::uint32_t>(tuple_proxy_info) == device_id;
            });
          return iterator;
        }

        std::vector<std::tuple<std::uint32_t, DeviceProxy>> proxy_list_ = {};
      };
    } // namespace proxys
  }   // namespace middleware
} // namespace agents
#endif
