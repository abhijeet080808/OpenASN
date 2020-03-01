#include "ElementSetSpec.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ElementSetSpec::
GetType() const
{
  return Production::ELEMENT_SET_SPEC;
}

bool
ElementSetSpec::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ElementSetSpec");

  // ElementSetSpecs ::=
  //   Unions
  // | ALL Exclusions

  size_t starting_index = asnDataIndex;

  auto obj = "Unions";
  LOG_START();
  auto unions =
    ProductionFactory::Get(Production::UNIONS);
  if (unions->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mUnions = unions;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ALL";
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

  obj = "Exclusions";
  LOG_START();
  auto exclusions =
    ProductionFactory::Get(Production::EXCLUSIONS);
  if (exclusions->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mExclusions = exclusions;
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
