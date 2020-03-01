#include "ComponentTypeList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ComponentTypeList::
GetType() const
{
  return Production::COMPONENT_TYPE_LIST;
}

bool
ComponentTypeList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ComponentTypeList");

  // ComponentTypeList ::=
  //   ComponentType
  // | ComponentTypeList "," ComponentType

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "ComponentType";
    LOG_START();
    auto component_type =
      ProductionFactory::Get(Production::COMPONENT_TYPE);
    if (component_type->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mComponentType.push_back(component_type);
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

  if (mComponentType.empty())
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
