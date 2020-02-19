#include "TeletexString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
TeletexString::
GetType() const
{
  return Production::TELETEX_STRING;
}

bool
TeletexString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // TeletexString

  LOG_START("TeletexString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "TeletexString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("TeletexString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("TeletexString", asnData);
    return false;
  }
}
