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

  auto obj = "ElementSetSpec";
  LOG_START();
  auto element_set_spec =
    ProductionFactory::Get(Production::ELEMENT_SET_SPEC);
  if (element_set_spec->Parse(asnData, asnDataIndex, endStop))
  {
    mElementSetSpec = element_set_spec;
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
