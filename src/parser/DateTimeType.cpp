#include "DateTimeType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

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
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // DateTimeType ::= DATE-TIME

  size_t starting_index = asnDataIndex;

  auto obj = "DATE-TIME";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
