#include "ModuleIdentifier.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ModuleIdentifier ::=
  // modulereference
  // DefinitiveIdentification

  LOG_START("ModuleReference", asnData);
  auto module_reference =
    ProductionFactory::Get(Production::MODULE_REFERENCE);
  if (module_reference->Parse(asnData, endStop))
  {
    mModuleReference = module_reference;
    LOG_PASS("ModuleReference", asnData);
  }
  else
  {
    LOG_FAIL("ModuleReference", asnData);
    return false;
  }

  LOG_START("DefinitiveIdentification", asnData);
  auto definitive_identification =
    ProductionFactory::Get(Production::DEFINITIVE_IDENTIFICATION);
	if (definitive_identification->Parse(asnData, endStop))
	{
    mDefinitiveIdentification = definitive_identification;
    LOG_PASS("DefinitiveIdentification", asnData);
  }
  else
  {
    LOG_FAIL("DefinitiveIdentification", asnData);
    return false;
	}

  return true;
}
