#include "RootEnumeration.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

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
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("RootEnumeration");

  // RootEnumeration ::= Enumeration

  size_t starting_index = asnDataIndex;

  auto obj = "Enumeration";
  LOG_START();
  auto enumeration =
    ProductionFactory::Get(Production::ENUMERATION);
  if (enumeration->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mEnumeration = enumeration;
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
