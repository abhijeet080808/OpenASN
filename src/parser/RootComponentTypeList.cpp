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
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("RootComponentTypeList");

  // RootComponentTypeList ::= ComponentTypeList

  size_t starting_index = asnDataIndex;

  auto obj = "ComponentTypeList";
  LOG_START();
  auto component_type_list =
    ProductionFactory::Get(Production::COMPONENT_TYPE_LIST);
  if (component_type_list->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mComponentTypeList = component_type_list;
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
