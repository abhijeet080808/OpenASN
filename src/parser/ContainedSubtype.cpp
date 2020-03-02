#include "ContainedSubtype.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ContainedSubtype::
GetType() const
{
  return Production::CONTAINED_SUBTYPE;
}

bool
ContainedSubtype::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ContainedSubtype");

  // ContainedSubtype ::= Includes Type

  size_t starting_index = asnDataIndex;

  auto obj = "Includes";
  LOG_START();
  auto includes =
    ProductionFactory::Get(Production::INCLUDES);
  if (includes->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mIncludes = includes;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "Type";
  LOG_START();
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mType = type;
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
