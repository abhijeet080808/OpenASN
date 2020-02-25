#include "AdditionalElementSetSpec.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
AdditionalElementSetSpec::
GetType() const
{
  return Production::ADDITIONAL_ELEMENT_SET_SPEC;
}

bool
AdditionalElementSetSpec::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // AdditionalElementSetSpec ::= ElementSetSpec

  size_t starting_index = asnDataIndex;

  auto obj = "AdditionalElementSetSpec";
  LOG_START();
  auto additional_element_set_spec =
    ProductionFactory::Get(Production::ADDITIONAL_ELEMENT_SET_SPEC);
  if (additional_element_set_spec->Parse(asnData, asnDataIndex, endStop))
  {
    mAdditionalElementSetSpec = additional_element_set_spec;
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
