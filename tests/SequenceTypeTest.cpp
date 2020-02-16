#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Rectangle.hh"

using namespace OpenASN;

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
