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
        explicit ProxyManager() :
            command_dispatcher_callback_(command_dispatcher_callback),
            message_command_dict_(message_command_dict) {}

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

        std::vector<std::tuple<std::uint32_t, DeviceProxy>> proxy_list_ = {};
      };
    } // namespace proxys
  }   // namespace middleware
} // namespace agents
#endif