#include "RootEnumeration.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RootEnumeration::
GetType() const
{
  return Production::ROOT_ENUMERATION;
}

bool
RootEnumeration::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // RootEnumeration ::= Enumeration

  LOG_START("Enumeration", asnData);
  auto enumeration =
    ProductionFactory::Get(Production::ENUMERATION);
  if (enumeration->Parse(asnData, endStop))
  {
    mEnumeration = enumeration;
    LOG_PASS("Enumeration", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("Enumeration", asnData);
    return false;
  }
}
