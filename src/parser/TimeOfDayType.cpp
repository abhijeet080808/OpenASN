#include "TimeOfDayType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
TimeOfDayType::
GetType() const
{
  return Production::TIME_OF_DAY_TYPE;
}

bool
TimeOfDayType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // TimeOfDayType ::= TIME-OF-DAY

  size_t starting_index = asnDataIndex;

  auto obj = "TIME-OF-DAY";
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
