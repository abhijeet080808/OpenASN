#include "UpperEndValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UpperEndValue::
GetType() const
{
  return Production::UPPER_END_VALUE;
}

bool
UpperEndValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("UpperEndValue");

  // UpperEndValue ::= Value | MAX

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

  obj = "Max";
  LOG_START();
  auto max =
    ProductionFactory::Get(Production::MAX);
  if (max->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mMax = max;
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
