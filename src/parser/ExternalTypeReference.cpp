#include "ExternalTypeReference.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ExternalTypeReference::
GetType() const
{
  return Production::EXTERNAL_TYPE_REFERENCE;
}

bool
ExternalTypeReference::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ExternalTypeReference ::= modulereference "." typereference

  size_t starting_index = asnDataIndex;

  auto obj = "ModuleReference";
  LOG_START();
  auto module_reference =
    ProductionFactory::Get(Production::MODULE_REFERENCE);
  if (module_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mModuleReference = module_reference;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
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
    return false;
  }

  obj = "TypeReference";
  LOG_START();
  auto type_reference =
    ProductionFactory::Get(Production::TYPE_REFERENCE);
  if (type_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mTypeReference = type_reference;
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
