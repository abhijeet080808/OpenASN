#include "ValueRange.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ValueRange::
GetType() const
{
  return Production::VALUE_RANGE;
}

bool
ValueRange::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ValueRange");

  // ValueRange ::= LowerEndpoint ".." UpperEndpoint

  size_t starting_index = asnDataIndex;

  auto obj = "LowerEndpoint";
  LOG_START();
  auto lower_endpoint =
    ProductionFactory::Get(Production::LOWER_ENDPOINT);
  if (lower_endpoint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mLowerEndpoint = lower_endpoint;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = ".";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = ".";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "UpperEndpoint";
  LOG_START();
  auto upper_endpoint =
    ProductionFactory::Get(Production::UPPER_ENDPOINT);
  if (upper_endpoint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mUpperEndpoint = upper_endpoint;
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