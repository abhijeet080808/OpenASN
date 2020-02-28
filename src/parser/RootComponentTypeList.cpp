#include "RootComponentTypeList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RootComponentTypeList::
GetType() const
{
  return Production::ROOT_COMPONENT_TYPE_LIST;
}

bool
RootComponentTypeList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // RootComponentTypeList ::= ComponentTypeList

  size_t starting_index = asnDataIndex;

  auto obj = "ComponentTypeList";
  LOG_START();
  auto component_type_list =
    ProductionFactory::Get(Production::COMPONENT_TYPE_LIST);
  if (component_type_list->Parse(asnData, asnDataIndex, endStop))
  {
    mComponentTypeList = component_type_list;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
