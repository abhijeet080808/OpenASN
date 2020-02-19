#include "T61String.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
T61String::
GetType() const
{
  return Production::T61_STRING;
}

bool
T61String::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // T61String

  LOG_START("T61String", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "T61String")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("T61String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("T61String", asnData);
    return false;
  }
}
