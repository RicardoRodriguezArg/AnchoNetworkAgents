#include <gtest/gtest.h>
#include "utils/utils.h"
#include "utils_tests_pack_unpack.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
