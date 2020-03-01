#include "ExternalValueReference.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ExternalValueReference::
GetType() const
{
  return Production::EXTERNAL_VALUE_REFERENCE;
}

bool
ExternalValueReference::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ExternalValueReference");

  // ExternalValueReference ::= modulereference "." valuereference

  size_t starting_index = asnDataIndex;

  auto obj = "ModuleReference";
  LOG_START();
  auto module_reference =
    ProductionFactory::Get(Production::MODULE_REFERENCE);
  if (module_reference->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mModuleReference = module_reference;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = ".";
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
}
