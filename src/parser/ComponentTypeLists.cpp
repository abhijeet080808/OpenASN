#include "ComponentTypeLists.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
ComponentTypeLists::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ComponentTypeLists ::=
  //   RootComponentTypeList
  // | RootComponentTypeList "," ExtensionAndException ExtensionAdditions OptionalExtensionMarker
  // | RootComponentTypeList "," ExtensionAndException ExtensionAdditions ExtensionEndMarker "," RootComponentTypeList
  // | ExtensionAndException ExtensionAdditions ExtensionEndMarker "," RootComponentTypeList
  // | ExtensionAndException ExtensionAdditions OptionalExtensionMarker

  LOG_START("RootComponentTypeList", asnData);
  auto root_component_type_list =
    ProductionFactory::Get(Production::ROOT_COMPONENT_TYPE_LIST);
  if (root_component_type_list->Parse(asnData, endStop))
  {
    mRootComponentTypeList = root_component_type_list;
    LOG_PASS("RootComponentTypeList", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RootComponentTypeList", asnData);
  }

  return false;
}
