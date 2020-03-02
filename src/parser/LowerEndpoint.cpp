#include "LowerEndpoint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
LowerEndpoint::
GetType() const
{
  return Production::LOWER_ENDPOINT;
}

bool
LowerEndpoint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("LowerEndpoint");

  // LowerEndpoint ::= LowerEndValue | LowerEndValue "<"

  size_t starting_index = asnDataIndex;

  auto obj = "LowerEndValue";
  LOG_START();
  auto lower_end_value =
    ProductionFactory::Get(Production::LOWER_END_VALUE);
  if (lower_end_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mLowerEndValue = lower_end_value;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "LessThan";
  LOG_START();
  auto less_than =
    ProductionFactory::Get(Production::LESS_THAN);
  if (less_than->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mLessThan = less_than;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }
}
