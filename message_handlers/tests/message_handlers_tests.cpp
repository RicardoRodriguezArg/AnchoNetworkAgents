#include "message_handlers/message_handlers.h"
#include <gtest/gtest.h>

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

namespace {
  class MessageHandlerFixture : public ::testing::Test {
  public:
    void SetUp() {}

    void TearDown() {}
  };

  TEST_F(MessageHandlerFixture, GivenValidInputUnpackIsOk) {}

} // namespace
