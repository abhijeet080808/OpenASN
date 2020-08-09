#include "Intersections.hh"

#include "ParseHelper.hh"
#include "ParseLog.hh"

#include "parser/ProductionFactory.hh"
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
Parse(
    size_t productionIndex,
    bool prodIndexPresent,
    const std::vector<Word>& asnData,
    size_t& asnDataIndex,
    std::vector<std::string>& endStop,
    std::vector<std::string>& parsePath,
    ProductionParseHistory& parseHistory)
{
  parsePath.push_back("Intersections" +
      (prodIndexPresent ? std::to_string(productionIndex) : ""));

  // Intersections ::=
  //   IntersectionElements
  // | IElems IntersectionMark IntersectionElements

  // IElems ::= Intersections

  // IntersectionMark ::= "^" | INTERSECTION

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "IntersectionElements" +
      std::to_string(mIntersectionElements.size());
    LOG_START();
    auto prod = ProductionFactory::Get(Production::INTERSECTION_ELEMENTS);
    if (prod->Parse(
          mIntersectionElements.size(),
          true,
          asnData,
          asnDataIndex,
          endStop,
          parsePath,
          parseHistory))
    {
      mIntersectionElements.push_back(prod);
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }

    obj = "^";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      LOG_PASS();
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
      ++asnDataIndex;
      LOG_PASS();
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
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
