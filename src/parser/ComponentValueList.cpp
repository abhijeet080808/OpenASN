#include "ComponentValueList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ComponentValueList::
GetType() const
{
  return Production::COMPONENT_VALUE_LIST;
}

bool
ComponentValueList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ComponentValueList");

  // ComponentValueList ::=
  //   NamedValue
  // | ComponentValueList "," NamedValue

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "NamedValue";
    LOG_START();
    auto named_value =
      ProductionFactory::Get(Production::NAMED_VALUE);
    if (named_value->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mNamedValue.push_back(named_value);
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

  if (mNamedValue.empty())
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
