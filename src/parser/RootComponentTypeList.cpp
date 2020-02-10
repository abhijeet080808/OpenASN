#include "RootComponentTypeList.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
RootComponentTypeList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // RootComponentTypeList ::= ComponentTypeList

  LOG_START("ComponentTypeList", asnData);
  auto component_type_list =
    ProductionFactory::Get(Production::COMPONENT_TYPE_LIST);
  if (component_type_list->Parse(asnData, endStop))
  {
    mComponentTypeList = component_type_list;
    LOG_PASS("ComponentTypeList", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("ComponentTypeList", asnData);
    return false;
  }
}
