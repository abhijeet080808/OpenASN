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
      std::vector<std::string>& endStop)
{
  // Elements ::=
  //   SubtypeElements
  // | ObjectSetElements
  // | "(" ElementSetSpec ")"

  size_t starting_index = asnDataIndex;

  auto obj = "SubtypeElements";
  LOG_START();
  auto subtype_elements =
    ProductionFactory::Get(Production::SUBTYPE_ELEMENTS);
  if (subtype_elements->Parse(asnData, asnDataIndex, endStop))
  {
    mSubtypeElements = subtype_elements;
    LOG_PASS();
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
  if (object_set_elements->Parse(asnData, asnDataIndex, endStop))
  {
    mObjectSetElements = object_set_elements;
    LOG_PASS();
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
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  endStop.push_back(")");

  obj = "ElementSetSpec";
  LOG_START();
  auto element_set_spec =
    ProductionFactory::Get(Production::ELEMENT_SET_SPEC);
  if (element_set_spec->Parse(asnData, asnDataIndex, endStop))
  {
    mElementSetSpe = element_set_spec;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = ")";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
