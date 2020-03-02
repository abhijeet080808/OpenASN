#include "UpperEndpoint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UpperEndpoint::
GetType() const
{
  return Production::UPPER_ENDPOINT;
}

bool
UpperEndpoint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("UpperEndpoint");

  // UpperEndpoint ::= UpperEndValue | "<" UpperEndValue

  size_t starting_index = asnDataIndex;

  auto obj = "LessThan";
  LOG_START();
  auto less_than =
    ProductionFactory::Get(Production::LESS_THAN);
  if (less_than->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mLessThan = less_than;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UpperEndValue";
  LOG_START();
  auto upper_end_value =
    ProductionFactory::Get(Production::UPPER_END_VALUE);
  if (upper_end_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mUpperEndValue = upper_end_value;
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
