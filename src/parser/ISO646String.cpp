#include "ISO646String.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ISO646String::
GetType() const
{
  return Production::ISO646_STRING;
}

bool
ISO646String::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // ISO646String

  LOG_START("ISO646String", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "ISO646String")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("ISO646String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("ISO646String", asnData);
    return false;
  }
}
