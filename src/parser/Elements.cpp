#include "Elements.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Elements::
GetType() const
{
  return Production::ELEMENTS;
}

bool
Elements::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Elements");

  // Elements ::=
  //   SubtypeElements
  // | ObjectSetElements
  // | "(" ElementSetSpec ")"

  size_t starting_index = asnDataIndex;

  auto obj = "SubtypeElements";
  LOG_START();
  auto subtype_elements =
    ProductionFactory::Get(Production::SUBTYPE_ELEMENTS);
  if (subtype_elements->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSubtypeElements = subtype_elements;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

#if 0
  obj = "ObjectSetElements";
  LOG_START();
  auto object_set_elements =
    ProductionFactory::Get(Production::OBJECT_SET_ELEMENTS);
  if (object_set_elements->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mObjectSetElements = object_set_elements;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }
#endif

  obj = "(";
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

  endStop.push_back(")");

  obj = "ElementSetSpec";
  LOG_START();
  auto element_set_spec =
    ProductionFactory::Get(Production::ELEMENT_SET_SPEC);
  if (element_set_spec->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mElementSetSpec = element_set_spec;
    endStop.pop_back();
    LOG_PASS();
  }
  else
  {
    endStop.pop_back();
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = ")";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
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
