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
      std::vector<std::string>& endStop)
{
  // Enumeration ::= EnumerationItem | EnumerationItem "," Enumeration

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "EnumerationItem";
    LOG_START();
    auto enumeration_item =
      ProductionFactory::Get(Production::ENUMERATION_ITEM);
    if (enumeration_item->Parse(asnData, asnDataIndex, endStop))
    {
      mEnumerationItem.push_back(enumeration_item);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      asnDataIndex = starting_index;
      return false;
    }

    obj = ",";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      LOG_PASS();
      ++asnDataIndex;
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
    return false;
  }
  else
  {
    return true;
  }
}
