#include "Intersections.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Intersections::
GetType() const
{
  return Production::INTERSECTIONS;
}

bool
Intersections::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Intersections ::=
  //   IntersectionElements
  // | IElems IntersectionMark IntersectionElements

  // IElems ::= Intersections

  // IntersectionMark ::= "^" | INTERSECTION

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "IntersectionElements";
    LOG_START();
    auto intersection_elements =
      ProductionFactory::Get(Production::INTERSECTION_ELEMENTS);
    if (intersection_elements->Parse(asnData, asnDataIndex, endStop))
    {
      mIntersectionElements.push_back(intersection_elements);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      asnDataIndex = starting_index;
      return false;
    }

    obj = "^";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      LOG_PASS();
      ++asnDataIndex;
      continue;
    }
    else
    {
      LOG_FAIL();
    }

    obj = "INTERSECTION";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      LOG_PASS();
      ++asnDataIndex;
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mIntersectionElements.empty())
  {
    asnDataIndex = starting_index;
    return false;
  }
  else
  {
    return true;
  }
}
