#include "UniversalString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UniversalString::
GetType() const
{
  return Production::UNIVERSAL_STRING;
}

bool
UniversalString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // UniversalString

  LOG_START("UniversalString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "UniversalString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("UniversalString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("UniversalString", asnData);
    return false;
  }
}
