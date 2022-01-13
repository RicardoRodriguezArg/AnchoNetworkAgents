#include "utils/utils.h"
#include <gtest/gtest.h>

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

using namespace agents;

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

  std::string CreateInputString(const InputStringCase &test_case) {
    std::string result{};
    switch (test_case) {
    case InputStringCase::kEmptyInputString: {
      result = std::string{};

    } break;
    case InputStringCase::kValid4BytesInputString: {
      result = "123XXXXXXXXXXXX";
    } break;
    default: {
    } break;
    }
    return result;
  }

  void CleanInputBuffer() {
    std::fill_n(raw_buffer_.begin(), agents::utils::MAX_BUFFER_SIZE, 0);
    raw_buffer_[511] = '\n';
  }

  agents::utils::PacketBuffer raw_buffer_;
};

TEST_F(UtilsPackUnpackMessage, GivenValidInputUnpackIsOk) {
  // Given valid input
  const auto &expected_input_message =
      CreateInputString(InputStringCase::kValid4BytesInputString);
  EXPECT_EQ(15U, expected_input_message.size());
  const auto result = agents::utils::PackMessageToString(
      expected_input_message, raw_buffer_.begin(),
      agents::common::MessageType::EVENT);
  ASSERT_TRUE(result);
  // First size at 4 first Bytes
  const auto data_size =
      agents::utils::GetPackectMessageSize(raw_buffer_.begin());
  ASSERT_TRUE(data_size.has_value());
  // Get Packect message type
  const auto message_type_opt = agents::utils::GetPackectMessageType(
      raw_buffer_.begin() + agents::utils::MESSAGE_SIZE_DEFAULT);
  ASSERT_TRUE(message_type_opt.has_value());
  const auto x = message_type_opt.value();
  EXPECT_EQ(static_cast<common::MessageType>(message_type_opt.value()),
            common::MessageType::EVENT);

  const auto enconded_data_size = data_size.value();
  EXPECT_EQ(expected_input_message.size(), enconded_data_size);

  // Check Enconded Message
  const auto encoded_data = agents::utils::GetPackectMessageData(
      raw_buffer_.begin() + agents::utils::MESSAGE_SIZE_DEFAULT +
          agents::utils::MESSAGE_TYPE_SIZE,
      enconded_data_size);
  ASSERT_TRUE(encoded_data.has_value());
  EXPECT_EQ(expected_input_message, encoded_data.value());
}

TEST_F(UtilsPackUnpackMessage, GivenInValidInputUnpackNotEncodec) {
  // Given valid input
  CleanInputBuffer();
  const auto &expected_input_message =
      CreateInputString(InputStringCase::kEmptyInputString);
  ASSERT_TRUE(expected_input_message.empty());
  const auto result = agents::utils::PackMessageToString(
      expected_input_message, raw_buffer_.begin(), common::MessageType::EVENT);
  ASSERT_FALSE(result);
}
