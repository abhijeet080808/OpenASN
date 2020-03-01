#include "DefinedValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DefinedValue::
GetType() const
{
  return Production::DEFINED_VALUE;
}

bool
DefinedValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("DefinedValue");

  // DefinedValue ::=
  //   ExternalValueReference
  // | valuereference
  // | ParameterizedValue

  size_t starting_index = asnDataIndex;

  auto obj = "ExternalValueReference";
  LOG_START();
  auto external_value_reference =
    ProductionFactory::Get(Production::EXTERNAL_VALUE_REFERENCE);
  if (external_value_reference->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mExternalValueReference = external_value_reference;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ValueReference";
  LOG_START();
  auto value_reference =
    ProductionFactory::Get(Production::VALUE_REFERENCE);
  if (value_reference->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mValueReference = value_reference;
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

  // ParameterizedValue
}
