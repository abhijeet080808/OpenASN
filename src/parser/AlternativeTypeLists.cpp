#include "AlternativeTypeLists.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
AlternativeTypeLists::
GetType() const
{
  return Production::ALTERNATIVE_TYPE_LISTS;
}

bool
AlternativeTypeLists::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // AlternativeTypeLists ::=
  //   RootAlternativeTypeList
  // | RootAlternativeTypeList "," ExtensionAndException ExtensionAdditionAlternatives OptionalExtensionMarker

  LOG_START("RootAlternativeTypeList", asnData);
  auto root_alternative_type_list =
    ProductionFactory::Get(Production::ROOT_ALTERNATIVE_TYPE_LIST);
  if (root_alternative_type_list->Parse(asnData, endStop))
  {
    mRootAlternativeTypeList = root_alternative_type_list;
    LOG_PASS("RootAlternativeTypeList", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RootAlternativeTypeList", asnData);
    return false;
  }
}
