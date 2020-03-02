#include "ElementSetSpecs.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ElementSetSpecs::
GetType() const
{
  return Production::ELEMENT_SET_SPECS;
}

bool
ElementSetSpecs::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ElementSetSpecs");

  // ElementSetSpecs ::=
  //   RootElementSetSpec
  // | RootElementSetSpec "," "..."
  // | RootElementSetSpec "," "..." "," AdditionalElementSetSpec

  size_t starting_index = asnDataIndex;

  auto obj = "RootElementSetSpec";
  LOG_START();
  auto root_element_set_spec =
    ProductionFactory::Get(Production::ROOT_ELEMENT_SET_SPEC);
  if (root_element_set_spec->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mRootElementSetSpec = root_element_set_spec;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = ",";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }

  obj = "Ellipsis";
  LOG_START();
  auto ellipsis =
    ProductionFactory::Get(Production::ELLIPSIS);
  if (ellipsis->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mEllipsis = ellipsis;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = ",";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }

  obj = "AdditionalElementSetSpec";
  LOG_START();
  auto additional_element_set_spec =
    ProductionFactory::Get(Production::ADDITIONAL_ELEMENT_SET_SPEC);
  if (additional_element_set_spec->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mAdditionalElementSetSpec = additional_element_set_spec;
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