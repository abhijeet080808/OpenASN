#include "IdentifierList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IdentifierList::
GetType() const
{
  return Production::IDENTIFIER_LIST;
}

bool
IdentifierList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ComponentTypeList");

  // IdentifierList ::=
  //   identifier
  // | IdentifierList "," identifier

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "Identifier";
    LOG_START();
    auto identifier =
      ProductionFactory::Get(Production::IDENTIFIER);
    if (identifier->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mIdentifier.push_back(identifier);
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }

    obj = ",";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mIdentifier.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
