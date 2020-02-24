#include "GeneralizedTime.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
GeneralizedTime::
GetType() const
{
  return Production::GENERALIZED_TIME;
}

bool
GeneralizedTime::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // GeneralizedTime

  size_t starting_index = asnDataIndex;

  auto obj = "GeneralizedTime";
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
