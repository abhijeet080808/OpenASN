#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "SequenceTypeTestSeq.hh"

using namespace OpenASN;
using namespace testing;

TEST(SequenceTypeTestSeq, CheckGetSet)
{
  SequenceTypeTestSeq dut;

  EXPECT_EQ(dut.GetSequenceTypeTestInt1().GetValue(), 0);
  EXPECT_EQ(dut.GetSequenceTypeTestInt2().GetValue(), 0);
  EXPECT_EQ(dut.GetSequenceTypeTestBool1().GetValue(), false);

  dut.SetSequenceTypeTestInt1(SequenceTypeTestInt1(100));
  EXPECT_EQ(dut.GetSequenceTypeTestInt1().GetValue(), 100);

  dut.SetSequenceTypeTestInt2(SequenceTypeTestInt2(100));
  EXPECT_EQ(dut.GetSequenceTypeTestInt2().GetValue(), 100);

  dut.SetSequenceTypeTestBool1(SequenceTypeTestBool1(true));
  EXPECT_EQ(dut.GetSequenceTypeTestBool1().GetValue(), true);
}

TEST(SequenceTypeTestSeq, CheckEncode)
{
  SequenceTypeTestSeq dut;

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

  buf.clear();
  dut.SetSequenceTypeTestInt1(127);
  dut.SetSequenceTypeTestInt2(128);
  dut.SetSequenceTypeTestBool1(true);
  EXPECT_EQ(dut.EncodeBER(buf), true);
  EXPECT_THAT(buf, ElementsAre(0x30,    // Tag    - SEQUENCE
                               0x0A,    // Length - SEQUENCE
                               0x02,    // Tag    - INTEGER
                               0x01,    // Length - INTEGER
                               0x7f,    // Value  - INTEGER
                               0x02,    // Tag    - INTEGER
                               0x02,    // Length - INTEGER
                               0x00,    // Value  - INTEGER
                               0x80,
                               0x01,    // Tag    - BOOLEAN
                               0x01,    // Length - BOOLEAN
                               0xff));  // Value  - BOOLEAN
}

TEST(SequenceTypeTestSeq, CheckDecode)
{
  SequenceTypeTestSeq dut;

  std::vector<uint8_t> buf{0x30, 0x0A, 0x02, 0x01, 0x7f, 0x02, 0x02, 0x00,
                           0x80, 0x01, 0x01, 0xff};
  EXPECT_EQ(dut.DecodeBER(buf), true);
  EXPECT_EQ(dut.GetSequenceTypeTestInt1().GetValue(), 127);
  EXPECT_EQ(dut.GetSequenceTypeTestInt2().GetValue(), 128);
  EXPECT_EQ(dut.GetSequenceTypeTestBool1().GetValue(), true);
  EXPECT_EQ(buf.empty(), true);
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
