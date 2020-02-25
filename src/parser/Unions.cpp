#include "Unions.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Unions::
GetType() const
{
  return Production::UNIONS;
}

bool
Unions::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Unions ::=
  //   Intersections
  // | UElems UnionMark Intersections

  // UElems ::= Unions

  // UnionMark ::= "|" | UNION

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "Intersections";
    LOG_START();
    auto intersections =
      ProductionFactory::Get(Production::INTERSECTIONS);
    if (intersections->Parse(asnData, asnDataIndex, endStop))
    {
      mIntersections.push_back(intersections);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      asnDataIndex = starting_index;
      return false;
    }

    obj = "|";
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

    obj = "UNION";
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

  if (mIntersections.empty())
  {
    asnDataIndex = starting_index;
    return false;
  }
  else
  {
    return true;
  }
}
