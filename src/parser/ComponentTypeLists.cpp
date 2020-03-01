#include "ComponentTypeLists.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ComponentTypeLists::
GetType() const
{
  return Production::COMPONENT_TYPE_LISTS;
}

bool
ComponentTypeLists::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ComponentTypeLists");

  // ComponentTypeLists ::=
  //   RootComponentTypeList
  // | RootComponentTypeList "," ExtensionAndException ExtensionAdditions OptionalExtensionMarker
  // | RootComponentTypeList "," ExtensionAndException ExtensionAdditions ExtensionEndMarker "," RootComponentTypeList
  // | ExtensionAndException ExtensionAdditions ExtensionEndMarker "," RootComponentTypeList
  // | ExtensionAndException ExtensionAdditions OptionalExtensionMarker

  size_t starting_index = asnDataIndex;

  auto obj = "RootComponentTypeList";
  LOG_START();
  auto root_component_type_list =
    ProductionFactory::Get(Production::ROOT_COMPONENT_TYPE_LIST);
  if (root_component_type_list->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mRootComponentTypeList = root_component_type_list;
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
