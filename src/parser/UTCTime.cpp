#include "UTCTime.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UTCTime::
GetType() const
{
  return Production::UTC_TIME;
}

bool
UTCTime::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // UTCTime

  size_t starting_index = asnDataIndex;

  auto obj = "UTCTime";
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
