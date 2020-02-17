#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Colored.hh"

using namespace OpenASN;
using namespace testing;

TEST(SimpleTypeTest, CheckGetSet)
{
  Colored dut;
  EXPECT_EQ(dut.GetValue(), false);

  dut.SetValue(true);
  EXPECT_EQ(dut.GetValue(), true);

  dut.SetValue(false);
  EXPECT_EQ(dut.GetValue(), false);
}

TEST(SimpleTypeTest, CheckEncode)
{
  Colored dut;
  std::vector<uint8_t> buf;
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x01, 0x01, 0x00));

  buf.clear();

  dut.SetValue(true);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x01, 0x01, 0xFF));
}

TEST(SimpleTypeTest, CheckDecode)
{
  Colored dut;
  std::vector<uint8_t> buf{0x01, 0x01, 0x00};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), false);

  buf = std::vector<uint8_t>{0x01, 0x01, 0xFF};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), true);
  EXPECT_EQ(buf.empty(), true);
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
