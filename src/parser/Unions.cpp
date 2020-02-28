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
      asnDataIndex = starting_index;
      LOG_FAIL();
      return false;
    }

    obj = "|";
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

    obj = "UNION";
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
