#include "DurationType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DurationType::
GetType() const
{
  return Production::DURATION_TYPE;
}

bool
DurationType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // DurationType ::= DURATION

  LOG_START("DURATION", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "DURATION")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("DURATION", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DURATION", asnData);
    return false;
  }
}
