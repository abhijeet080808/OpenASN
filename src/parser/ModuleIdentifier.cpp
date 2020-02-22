#include "ModuleIdentifier.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ModuleIdentifier::
GetType() const
{
  return Production::MODULE_IDENTIFIER;
}

bool
ModuleIdentifier::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ModuleIdentifier ::=
  // modulereference
  // DefinitiveIdentification

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
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "DefinitiveIdentification";
  LOG_START();
  auto definitive_identification =
    ProductionFactory::Get(Production::DEFINITIVE_IDENTIFICATION);
  if (definitive_identification->Parse(asnData, asnDataIndex, endStop))
  {
    mDefinitiveIdentification = definitive_identification;
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
