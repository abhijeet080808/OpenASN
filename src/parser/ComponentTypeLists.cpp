#include "ComponentTypeLists.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
ComponentTypeLists::
Parse(AsnData&, const std::vector<std::string>&) //AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ComponentTypeLists ::=
  //   RootComponentTypeList
  // | RootComponentTypeList "," ExtensionAndException ExtensionAdditions OptionalExtensionMarker
  // | RootComponentTypeList "," ExtensionAndException ExtensionAdditions ExtensionEndMarker "," RootComponentTypeList
  // | ExtensionAndException ExtensionAdditions ExtensionEndMarker "," RootComponentTypeList
  // | ExtensionAndException ExtensionAdditions OptionalExtensionMarker


  return true;
}
