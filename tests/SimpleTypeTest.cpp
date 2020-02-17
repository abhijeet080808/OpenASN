#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "SimpleTypeTestBool.hh"
#include "SimpleTypeTestInt.hh"

using namespace OpenASN;
using namespace testing;

TEST(SimpleTypeTestBool, CheckGetSet)
{
  SimpleTypeTestBool dut;
  EXPECT_EQ(dut.GetValue(), false);

  dut.SetValue(true);
  EXPECT_EQ(dut.GetValue(), true);

  dut.SetValue(false);
  EXPECT_EQ(dut.GetValue(), false);
}

TEST(SimpleTypeTestBool, CheckEncode)
{
  SimpleTypeTestBool dut;
  std::vector<uint8_t> buf;
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x01, 0x01, 0x00));

  buf.clear();
  dut.SetValue(true);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x01, 0x01, 0xFF));
}

TEST(SimpleTypeTestBool, CheckDecode)
{
  SimpleTypeTestBool dut;
  std::vector<uint8_t> buf{0x01, 0x01, 0x00};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), false);
  EXPECT_EQ(buf.empty(), true);

  buf = std::vector<uint8_t>{0x01, 0x01, 0xFF};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), true);
  EXPECT_EQ(buf.empty(), true);
}

TEST(SimpleTypeTestInt, CheckGetSet)
{
  SimpleTypeTestInt dut;
  EXPECT_EQ(dut.GetValue(), 0);

  dut.SetValue(1234567891234567l);
  EXPECT_EQ(dut.GetValue(), 1234567891234567l);

  dut.SetValue(-1234567891234567l);
  EXPECT_EQ(dut.GetValue(), -1234567891234567l);
}

TEST(SimpleTypeTestInt, CheckEncode)
{
  SimpleTypeTestInt dut;
  std::vector<uint8_t> buf;
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x02, 0x01, 0x00));

  buf.clear();
  dut.SetValue(12345);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x02, 0x02, 0x30, 0x39));

  buf.clear();
  dut.SetValue(-12345);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x02, 0x02, 0xcf, 0xc7));

  buf.clear();
  dut.SetValue(140737488617600l);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x02, 0x07, 0x00, 0x80, 0x00, 0x00, 0x04, 0x00,
                               0x80));

  buf.clear();
  dut.SetValue(-140737488617600l);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x02, 0x07, 0xff, 0x7f, 0xff, 0xff, 0xfb, 0xff,
                               0x80));
}

TEST(SimpleTypeTestInt, CheckDecode)
{
  SimpleTypeTestInt dut;
  std::vector<uint8_t> buf{0x02, 0x02, 0x30, 0x39};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), 12345);
  EXPECT_EQ(buf.empty(), true);

  buf = std::vector<uint8_t>{0x02, 0x02, 0xcf, 0xc7};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), -12345);
  EXPECT_EQ(buf.empty(), true);

  buf = std::vector<uint8_t>{0x02, 0x07, 0x00, 0x80, 0x00, 0x00, 0x04, 0x00,
                             0x80};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), 140737488617600l);
  EXPECT_EQ(buf.empty(), true);

  buf = std::vector<uint8_t>{0x02, 0x07, 0xff, 0x7f, 0xff, 0xff, 0xfb, 0xff,
                             0x80};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetValue(), -140737488617600l);
  EXPECT_EQ(buf.empty(), true);
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
