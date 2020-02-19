#include "NumericString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NumericString::
GetType() const
{
  return Production::NUMERIC_STRING;
}

bool
NumericString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // NumericString

  LOG_START("NumericString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "NumericString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("NumericString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NumericString", asnData);
    return false;
  }
}
