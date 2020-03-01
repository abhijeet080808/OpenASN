#include "Enumeration.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Enumeration::
GetType() const
{
  return Production::ENUMERATION;
}

bool
Enumeration::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Enumeration");

  // Enumeration ::= EnumerationItem | EnumerationItem "," Enumeration

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "EnumerationItem";
    LOG_START();
    auto enumeration_item =
      ProductionFactory::Get(Production::ENUMERATION_ITEM);
    if (enumeration_item->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mEnumerationItem.push_back(enumeration_item);
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

  if (mEnumerationItem.empty())
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
