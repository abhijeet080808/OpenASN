#include "Universal.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Universal::
GetType() const
{
  return Production::UNIVERSAL;
}

bool
Universal::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // UNIVERSAL

  size_t starting_index = asnDataIndex;

  auto obj = "UNIVERSAL";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
