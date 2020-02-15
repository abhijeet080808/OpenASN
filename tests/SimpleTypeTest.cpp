#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Colored.hh"

using namespace OpenASN;

TEST_CASE("SimpleTypeTest")
{
  Colored dut;

  SECTION("Checking getters/setters")
  {
    CHECK(dut.GetValue() == false);

    dut.SetValue(true);
    CHECK(dut.GetValue() == true);

    dut.SetValue(false);
    CHECK(dut.GetValue() == false);
  }

  SECTION("Checking encode")
  {
    std::vector<uint8_t> buf;
    CHECK(dut.EncodeBER(buf) == true);
    CHECK(buf == std::vector<uint8_t>{0x01, 0x01, 0x00});

    buf.clear();

    dut.SetValue(true);
    CHECK(dut.EncodeBER(buf) == true);
    CHECK(buf == std::vector<uint8_t>{0x01, 0x01, 0xFF});
  }

  SECTION("Checking decode")
  {
    std::vector<uint8_t> buf{0x01, 0x01, 0x00};
    CHECK(dut.DecodeBER(buf) == true);
    CHECK(dut.GetValue() == false);

    buf = std::vector<uint8_t>{0x01, 0x01, 0xFF};
    CHECK(dut.DecodeBER(buf) == true);
    CHECK(dut.GetValue() == true);
    CHECK(buf.empty());
  }
}
