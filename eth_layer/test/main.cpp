#include "eth_layer/udp_client.h"
#include "eth_layer/udp_server.h"
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
