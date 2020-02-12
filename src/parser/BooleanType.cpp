#include "BooleanType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BooleanType::
GetType() const
{
  return Production::BOOLEAN_TYPE;
}

bool
BooleanType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // BooleanType ::= BOOLEAN

  LOG_START("BOOLEAN", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "BOOLEAN")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("BOOLEAN", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BOOLEAN", asnData);
    return false;
  }
}
