#include "T61String.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
T61String::
GetType() const
{
  return Production::T61_STRING;
}

bool
T61String::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // T61String

  size_t starting_index = asnDataIndex;

  auto obj = "T61String";
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
