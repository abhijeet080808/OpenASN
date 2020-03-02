#include "LowerEndValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
LowerEndValue::
GetType() const
{
  return Production::LOWER_END_VALUE;
}

bool
LowerEndValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("LowerEndValue");

  // LowerEndValue ::= Value | MIN

  size_t starting_index = asnDataIndex;

  auto obj = "Value";
  LOG_START();
  auto value =
    ProductionFactory::Get(Production::VALUE);
  if (value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mValue = value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Min";
  LOG_START();
  auto min =
    ProductionFactory::Get(Production::MIN);
  if (min->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mMin = min;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
