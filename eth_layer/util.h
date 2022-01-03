#ifndef _ETH_LAYER_UTILS_H__
#define _ETH_LAYER_UTILS_H__
#include <chrono>
#include <cstdint>

namespace agents {
namespace communication {

template <typename Type>
Type GetMaxValue(Type first, Type second) {
  return std::max(first, second);
}

std::uint64_t GetCurrentTime() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}

}  // namespace communication
}  // namespace agents
#endif