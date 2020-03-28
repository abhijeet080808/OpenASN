#include "SubsequentArcIdentifier.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SubsequentArcIdentifier::
GetType() const
{
  return Production::SUBSEQUENT_ARC_IDENTIFIER;
}

bool
SubsequentArcIdentifier::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SubsequentArcIdentifier");

  // SubsequentArcIdentifier ::=
  //   "/" ArcIdentifier SubsequentArcIdentifier
  // | empty

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "/";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }

    obj = "ArcIdentifier";
    LOG_START();
    auto arc_identifier =
      ProductionFactory::Get(Production::ARC_IDENTIFIER);
    if (arc_identifier->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mArcIdentifier.push_back(arc_identifier);
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }
  }

  parsePath.pop_back();
  return true;
}
