#include "TimeType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
TimeType::
GetType() const
{
  return Production::TIME_TYPE;
}

bool
TimeType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // TimeType ::= TIME

  size_t starting_index = asnDataIndex;

  auto obj = "TIME";
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
