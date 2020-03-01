#include "UsefulType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UsefulType::
GetType() const
{
  return Production::USEFUL_TYPE;
}

bool
UsefulType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("UsefulType");

  // UsefulType ::=
  //   GeneralizedTime
  // | UTCTime
  // | ObjectDescriptor

  size_t starting_index = asnDataIndex;

  auto obj = "GeneralizedTime";
  LOG_START();
  auto generalized_time =
    ProductionFactory::Get(Production::GENERALIZED_TIME);
  if (generalized_time->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mGeneralizedTime = generalized_time;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UTCTime";
  LOG_START();
  auto utc_time =
    ProductionFactory::Get(Production::UTC_TIME);
  if (utc_time->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mUTCTime = utc_time;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ObjectDescriptor";
  LOG_START();
  auto object_descriptor =
    ProductionFactory::Get(Production::OBJECT_DESCRIPTOR);
  if (object_descriptor->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mObjectDescriptor = object_descriptor;
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
