#ifndef __ETH_LAYER_RESOURCE_MANAGER__
#define __ETH_LAYER_RESOURCE_MANAGER__

#include "eth_layer/commons.h"

#include <vector>

namespace agent {
namespace communication {
struct ResourceManager {
  void AddAddress(std::unique_ptr<struct addrinfo> address) {
    releaseAddressQueue_.push_back(std::move(address));
  }

  std::vector<std::unique_ptr<struct addrinfo>> releaseAddressQueue_;
};
}  // namespace communication
}  // namespace agent

#endif
