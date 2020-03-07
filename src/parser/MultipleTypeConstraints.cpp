#include "MultipleTypeConstraints.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
MultipleTypeConstraints::
GetType() const
{
  return Production::MULTIPLE_TYPE_CONSTRAINTS;
}

bool
MultipleTypeConstraints::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("MultipleTypeConstraints");

  // MultipleTypeConstraints ::=
  //   FullSpecification
  // | PartialSpecification

  size_t starting_index = asnDataIndex;

  auto obj = "FullSpecification";
  LOG_START();
  auto full_specification =
    ProductionFactory::Get(Production::FULL_SPECIFICATION);
  if (full_specification->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mFullSpecification = full_specification;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "PartialSpecification";
  LOG_START();
  auto partial_specification =
    ProductionFactory::Get(Production::PARTIAL_SPECIFICATION);
  if (partial_specification->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPartialSpecification = partial_specification;
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
