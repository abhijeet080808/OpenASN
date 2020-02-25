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
      std::vector<std::string>& endStop)
{
  // SubtypeConstraint ::= ElementSetSpecs

  size_t starting_index = asnDataIndex;

  auto obj = "ElementSetSpecs";
  LOG_START();
  auto element_set_specs =
    ProductionFactory::Get(Production::ELEMENT_SET_SPECS);
  if (element_set_specs->Parse(asnData, asnDataIndex, endStop))
  {
    mElementSetSpecs = element_set_specs;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
