#include <gtest/gtest.h>
#include "utils/utils.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;



class UtilsPackUnpackMessage : public ::testing::Test {
 public:
  enum class InputStringCase {
    kEmptyInputString,
    kValid4BytesInputString,

  };

  UtilsPackUnpackMessage() {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~UtilsPackUnpackMessage() {
    // cleanup any pending stuff, but no exceptions allowed
  }

  std::string CreateInputString(const InputStringCase& test_case) {
    std::string result{};
    switch (test_case) {
	    case InputStringCase::kEmptyInputString: {
        result.clear();
      }
	    case InputStringCase::kValid4BytesInputString: {
        result = "xxxx";
      }
      default: { }
    }
    return result;
  }
};

// Demonstrate some basic assertions.
TEST(UtilsPackUnpackMessage, GivenValidInputUnpackIsOk) {
  // Given valid input
  const auto& valid_input =
      CreateInputString(InputStringCase::kValid4BytesInputString);
  EXPECT_EQ(4U, valid_input.size());
  const auto result = agents::utils::UnpackMessage(valid_input);
  ASSERT_TRUE(result.has_value());
}
