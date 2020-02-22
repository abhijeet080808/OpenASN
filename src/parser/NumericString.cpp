#include "NumericString.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NumericString::
GetType() const
{
  return Production::NUMERIC_STRING;
}

bool
NumericString::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // NumericString

  size_t starting_index = asnDataIndex;

  auto obj = "NumericString";
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
