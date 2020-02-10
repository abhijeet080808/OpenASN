#include "NamedType.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
NamedType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NamedType ::= identifier Type

  LOG_START("Identifier", asnData);
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, endStop))
  {
    mIdentifier = identifier;
    LOG_PASS("Identifier", asnData);
  }
  else
  {
    LOG_FAIL("Identifier", asnData);
    return false;
  }

  LOG_START("Type", asnData);
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, endStop))
  {
    mType = type;
    LOG_PASS("Type", asnData);
  }
  else
  {
    LOG_FAIL("Type", asnData);
    return false;
  }

  return true;
}
