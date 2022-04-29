#include "eth_layer/udp_server.h"
#include <gtest/gtest.h>
#include <thread>

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

using namespace agents;
namespace {
  struct UpdLayerTestFixture : public ::testing::Test {
    void SetUp() { udp_server_.InitServer(); }

    void TearDown() { udp_server_.StopServer(); }

    void RunServerAsync() {
      // std::array<char, MAX_BUFFER_SIZE> buffer;
      // std::future<std::string> resultFromDB = std::async(std::launch::async,
      // agents::communication::udp::Server::ReadFromAllClients, buffer);
    }

    static constexpr std::uint16_t kServerPort{5001};
    agents::communication::udp::Server udp_server_{kServerPort};
  };

  TEST_F(UpdLayerTestFixture, GivenValidStateWhenSetupUdpServerThenServerIsOperational) {
    ASSERT_TRUE(udp_server_.IsOperational());
  }

  TEST_F(UpdLayerTestFixture, GivenValidStateWhenSetupClientAndServerThenClientReceiveMessage) {
    ASSERT_TRUE(udp_server_.IsOperational());
  }
} // namespace
