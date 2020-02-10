#include "ModuleDefinition.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
ModuleDefinition::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
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

  std::vector<std::string> end_stop{ "DEFINITIONS" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  LOG_START("ModuleIdentifier", asnData);
  auto module_identifier =
    ProductionFactory::Get(Production::MODULE_IDENTIFIER);
  if (module_identifier->Parse(asnData, end_stop))
  {
    mModuleIdentifier = module_identifier;
    LOG_PASS("ModuleIdentifier", asnData);
  }
  else
  {
    LOG_FAIL("ModuleIdentifier", asnData);
    return false;
  }

  LOG_START("DEFINITIONS", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "DEFINITIONS")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("DEFINITIONS", asnData);
  }
  else
  {
    LOG_FAIL("DEFINITIONS", asnData);
    return false;
  }

  LOG_START(":", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == ":")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS(":", asnData);
  }
  else
  {
    LOG_FAIL(":", asnData);
    return false;
  }

  LOG_START(":", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == ":")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS(":", asnData);
  }
  else
  {
    LOG_FAIL(":", asnData);
    return false;
  }

  LOG_START("=", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "=")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("=", asnData);
  }
  else
  {
    LOG_FAIL("=", asnData);
    return false;
  }

  LOG_START("BEGIN", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "BEGIN")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("BEGIN", asnData);
  }
  else
  {
    LOG_FAIL("BEGIN", asnData);
    return false;
  }

  LOG_START("ModuleBody", asnData);
  auto module_body =
    ProductionFactory::Get(Production::MODULE_BODY);
  if (module_body->Parse(asnData, end_stop))
  {
    mModuleBody = module_body;
    LOG_PASS("ModuleBody", asnData);
  }
  else
  {
    LOG_FAIL("ModuleBody", asnData);
    return false;
  }

  LOG_START("END", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "END")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("END", asnData);
  }
  else
  {
    LOG_FAIL("END", asnData);
    return false;
  }

  return true;
}

