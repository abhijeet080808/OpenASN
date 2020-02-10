#include "NameForm.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
NameForm::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NameForm ::= identifier

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

  return true;
}
