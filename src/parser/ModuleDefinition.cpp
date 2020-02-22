#include "ModuleDefinition.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ModuleDefinition::
GetType() const
{
  return Production::MODULE_DEFINITION;
}

bool
ModuleDefinition::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ModuleDefinition ::=
  // ModuleIdentifier
  // DEFINITIONS
  // EncodingReferenceDefault
  // TagDefault
  // ExtensionDefault
  // "::="
  // BEGIN
  // ModuleBody
  // EncodingControlSections
  // END

  size_t starting_index = asnDataIndex;

  endStop.push_back("DEFINITIONS");

  auto obj = "ModuleIdentifier";
  LOG_START();
  auto module_identifier =
    ProductionFactory::Get(Production::MODULE_IDENTIFIER);
  if (module_identifier->Parse(asnData, asnDataIndex, endStop))
  {
    mModuleIdentifier = module_identifier;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "DEFINITIONS";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = ":";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = ":";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "=";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "BEGIN";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  endStop.push_back("END");

  obj = "ModuleBody";
  LOG_START();
  auto module_body =
    ProductionFactory::Get(Production::MODULE_BODY);
  if (module_body->Parse(asnData, asnDataIndex, endStop))
  {
    mModuleBody = module_body;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "END";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}

