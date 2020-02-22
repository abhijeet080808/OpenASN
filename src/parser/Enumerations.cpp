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
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Enumerations ::=
  //   RootEnumeration
  // | RootEnumeration "," " ... " ExceptionSpec
  // | RootEnumeration "," " ... " ExceptionSpec "," AdditionalEnumeration

  size_t starting_index = asnDataIndex;

  auto obj = "RootEnumeration";
  LOG_START();
  auto root_enumeration =
    ProductionFactory::Get(Production::ROOT_ENUMERATION);
  if (root_enumeration->Parse(asnData, asnDataIndex, endStop))
  {
    mRootEnumeration = root_enumeration;
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
