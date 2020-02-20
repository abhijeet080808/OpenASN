#include "DateType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DateType::
GetType() const
{
  return Production::DATE_TYPE;
}

bool
DateType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // DateType ::= DATE

  LOG_START("DATE", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "DATE")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("DATE", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DATE", asnData);
    return false;
  }
}
