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

  UtilsPackUnpackMessage() { CleanInputBuffer(); }

  void SetUp() {}

  void TearDown() { CleanInputBuffer(); }

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
        result = "123XXXXXXXXXXXX";
      }
      default: {}
    }
    return result;
  }

  void CleanInputBuffer() {
    std::fill_n(raw_buffer_, agents::utils::MAX_BUFFER_SIZE, 0);
    raw_buffer_[511] = '\n';
  }

  agents::utils::PacketBuffer raw_buffer_;
};

TEST_F(UtilsPackUnpackMessage, GivenValidInputUnpackIsOk) {
  // Given valid input
  const auto& expected_input_message =
      CreateInputString(InputStringCase::kValid4BytesInputString);
  EXPECT_EQ(15U, expected_input_message.size());
  const auto result = agents::utils::PackMessageToString(expected_input_message,
                                                         raw_buffer_.begin());
  ASSERT_TRUE(result.has_value());
  auto raw_data = result.value();
  // First size at 4 first Bytes
  const auto data_size = agents::utils::GetPackectMessageSize(raw_data.begin());
  ASSERT_TRUE(data_size.has_value());
  const auto enconded_data_size = data_size.value();
  EXPECT_EQ(expected_input_message.size(), enconded_data_size);
  // Check Enconded Message
  const auto encoded_data = agents::utils::GetPackectMessageData(
      raw_data.begin(), enconded_data_size);
  ASSERT_TRUE(encoded_data.has_value());
  EXPECT_EQ(expected_input_message, encoded_data.value());
}
