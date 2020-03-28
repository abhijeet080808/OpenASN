#include "FirstArcIdentifier.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
FirstArcIdentifier::
GetType() const
{
  return Production::FIRST_ARC_IDENTIFIER;
}

bool
FirstArcIdentifier::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("FirstArcIdentifier");

  // FirstArcIdentifier ::= "/" ArcIdentifier

  size_t starting_index = asnDataIndex;

  auto obj = "/";
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

  obj = "ArcIdentifier";
  LOG_START();
  auto arc_identifier =
    ProductionFactory::Get(Production::ARC_IDENTIFIER);
  if (arc_identifier->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mArcIdentifier = arc_identifier;
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
