#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Rectangle.hh"

using namespace OpenASN;
using namespace testing;


TEST(SequenceTypeTest, CheckGetSet)
{
  Rectangle dut;

  EXPECT_EQ(dut.GetHeight().GetValue(), 0);
  EXPECT_EQ(dut.GetWidth().GetValue(), 0);
  EXPECT_EQ(dut.GetBordered().GetValue(), false);

  dut.SetHeight(Height(100));
  EXPECT_EQ(dut.GetHeight().GetValue(), 100);

  dut.SetWidth(Width(100));
  EXPECT_EQ(dut.GetWidth().GetValue(), 100);

  dut.SetBordered(Bordered(true));
  EXPECT_EQ(dut.GetBordered().GetValue(), true);
}

TEST(SequenceTypeTest, CheckEncode)
{
  Rectangle dut;

  std::vector<uint8_t> buf;
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x30,    // Tag    - SEQUENCE
                               0x09,    // Length - SEQUENCE
                               0x02,    // Tag    - INTEGER
                               0x01,    // Length - INTEGER
                               0x00,    // Value  - INTEGER
                               0x02,    // Tag    - INTEGER
                               0x01,    // Length - INTEGER
                               0x00,    // Value  - INTEGER
                               0x01,    // Tag    - BOOLEAN
                               0x01,    // Length - BOOLEAN
                               0x00));  // Value  - BOOLEAN
}

#if 0
TEST_CASE("SequenceTypeTest")
{
  Rectangle dut;

  SECTION("Checking getters/setters")
  {
    CHECK(dut.GetHeight().GetValue() == 0);
    CHECK(dut.GetWidth().GetValue() == 0);
    CHECK(dut.GetBordered().GetValue() == false);

    dut.SetHeight(Height(100));
    CHECK(dut.GetHeight().GetValue() == 100);

    dut.SetWidth(Width(100));
    CHECK(dut.GetWidth().GetValue() == 100);

    dut.SetBordered(Bordered(true));
    CHECK(dut.GetBordered().GetValue() == true);
  }

  SECTION("Checking encode")
  {
    std::vector<uint8_t> buf;
    CHECK(dut.EncodeBER(buf) == true);
    /*CHECK(buf == std::vector<uint8_t>{0x01, 0x01, 0x00});

    buf.clear();

    dut.SetHeight(127);
    dut.SetWidth(128);
    dut.SetBordered(true);
    CHECK(dut.EncodeBER(buf) == true);
    CHECK(buf == std::vector<uint8_t>{0x01, 0x01, 0xFF});*/
  }

  SECTION("Checking decode")
  {
    /*
    std::vector<uint8_t> buf{0x01, 0x01, 0x00};
    CHECK(dut.DecodeBER(buf) == true);
    CHECK(dut.GetHeight() == 0);
    CHECK(dut.GetWidth() == 0);
    CHECK(dut.GetBordered() == false);

    buf = std::vector<uint8_t>{0x01, 0x01, 0xFF};
    CHECK(dut.DecodeBER(buf) == true);
    CHECK(dut.GetHeight() == 0);
    CHECK(dut.GetWidth() == 0);
    CHECK(dut.GetBordered() == true);
    CHECK(buf.empty());*/
  }
}
#endif

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
