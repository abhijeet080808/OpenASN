#include "UnrestrictedCharacterStringType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UnrestrictedCharacterStringType::
GetType() const
{
  return Production::UNRESTRICTED_CHARACTER_STRING_TYPE;
}

bool
UnrestrictedCharacterStringType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // UnrestrictedCharacterStringType ::= CHARACTER STRING

  LOG_START("CHARACTER", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "CHARACTER")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("CHARACTER", asnData);
  }
  else
  {
    LOG_FAIL("CHARACTER", asnData);
    return false;
  }

  LOG_START("STRING", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "STRING")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("STRING", asnData);
  }
  else
  {
    LOG_FAIL("STRING", asnData);
    return false;
  }

  return true;
}
