#include "RealType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RealType::
GetType() const
{
  return Production::REAL_TYPE;
}

bool
RealType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // RealType ::= REAL

  LOG_START("REAL", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "REAL")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("REAL", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("REAL", asnData);
    return false;
  }
}
