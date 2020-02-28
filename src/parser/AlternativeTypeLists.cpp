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
      std::vector<std::string>& endStop)
{
  // AlternativeTypeLists ::=
  //   RootAlternativeTypeList
  // | RootAlternativeTypeList "," ExtensionAndException ExtensionAdditionAlternatives OptionalExtensionMarker

  size_t starting_index = asnDataIndex;

  auto obj = "RootAlternativeTypeList";
  LOG_START();
  auto root_alternative_type_list =
    ProductionFactory::Get(Production::ROOT_ALTERNATIVE_TYPE_LIST);
  if (root_alternative_type_list->Parse(asnData, asnDataIndex, endStop))
  {
    mRootAlternativeTypeList = root_alternative_type_list;
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
