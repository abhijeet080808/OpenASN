#include "Enumerations.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Enumerations::
GetType() const
{
  return Production::ENUMERATIONS;
}

bool
Enumerations::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // Enumerations ::=
  //   RootEnumeration
  // | RootEnumeration "," " ... " ExceptionSpec
  // | RootEnumeration "," " ... " ExceptionSpec "," AdditionalEnumeration

  LOG_START("RootEnumeration", asnData);
  auto root_enumeration =
    ProductionFactory::Get(Production::ROOT_ENUMERATION);
  if (root_enumeration->Parse(asnData, endStop))
  {
    mRootEnumeration = root_enumeration;
    LOG_PASS("RootEnumeration", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RootEnumeration", asnData);
    return false;
  }
}
