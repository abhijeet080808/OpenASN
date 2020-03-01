#include "AlternativeTypeLists.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

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
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("AlternativeTypeLists");

  // AlternativeTypeLists ::=
  //   RootAlternativeTypeList
  // | RootAlternativeTypeList "," ExtensionAndException ExtensionAdditionAlternatives OptionalExtensionMarker

  size_t starting_index = asnDataIndex;

  auto obj = "RootAlternativeTypeList";
  LOG_START();
  auto root_alternative_type_list =
    ProductionFactory::Get(Production::ROOT_ALTERNATIVE_TYPE_LIST);
  if (root_alternative_type_list->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mRootAlternativeTypeList = root_alternative_type_list;
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
