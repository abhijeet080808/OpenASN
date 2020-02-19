#include "UTF8String.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UTF8String::
GetType() const
{
  return Production::UTF8_STRING;
}

bool
UTF8String::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // UTF8String

  LOG_START("UTF8String", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "UTF8String")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("UTF8String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("UTF8String", asnData);
    return false;
  }
}
