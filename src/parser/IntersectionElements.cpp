#include "IntersectionElements.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IntersectionElements::
GetType() const
{
  return Production::INTERSECTION_ELEMENTS;
}

bool
IntersectionElements::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // IntersectionElements ::=
  //   Elements
  // | Elems Exclusions

  // Elems ::= Elements

  // Exclusions ::= EXCEPT Elements

  size_t starting_index = asnDataIndex;

  auto obj = "Elements";
  LOG_START();
  auto elements =
    ProductionFactory::Get(Production::ELEMENTS);
  if (elements->Parse(asnData, asnDataIndex, endStop))
  {
    mElements = elements;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }

  obj = "EXCEPT";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    return true;
  }

  obj = "Elements";
  LOG_START();
  elements =
    ProductionFactory::Get(Production::ELEMENTS);
  if (elements->Parse(asnData, asnDataIndex, endStop))
  {
    mExceptElements = elements;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
