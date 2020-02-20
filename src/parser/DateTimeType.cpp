#include "DateTimeType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DateTimeType::
GetType() const
{
  return Production::DATE_TIME_TYPE;
}

bool
DateTimeType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // DateTimeType ::= DATE-TIME

  LOG_START("DATE-TIME", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "DATE-TIME")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("DATE-TIME", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("DATE-TIME", asnData);
    return false;
  }
}
