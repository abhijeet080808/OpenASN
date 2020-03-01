#include "SubtypeConstraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SubtypeConstraint::
GetType() const
{
  return Production::SUBTYPE_CONSTRAINT;
}

bool
SubtypeConstraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SubtypeConstraint");

  // SubtypeConstraint ::= ElementSetSpecs

  size_t starting_index = asnDataIndex;

  auto obj = "ElementSetSpecs";
  LOG_START();
  auto element_set_specs =
    ProductionFactory::Get(Production::ELEMENT_SET_SPECS);
  if (element_set_specs->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mElementSetSpecs = element_set_specs;
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
