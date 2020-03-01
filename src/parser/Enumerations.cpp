#include "Enumerations.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

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
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Enumerations");

  // Enumerations ::=
  //   RootEnumeration
  // | RootEnumeration "," " ... " ExceptionSpec
  // | RootEnumeration "," " ... " ExceptionSpec "," AdditionalEnumeration

  size_t starting_index = asnDataIndex;

  auto obj = "RootEnumeration";
  LOG_START();
  auto root_enumeration =
    ProductionFactory::Get(Production::ROOT_ENUMERATION);
  if (root_enumeration->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mRootEnumeration = root_enumeration;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
