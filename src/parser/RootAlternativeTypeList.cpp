#include "RootAlternativeTypeList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RootAlternativeTypeList::
GetType() const
{
  return Production::ROOT_ALTERNATIVE_TYPE_LIST;
}

bool
RootAlternativeTypeList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // RootAlternativeTypeList ::= AlternativeTypeList

  size_t starting_index = asnDataIndex;

  auto obj = "AlternativeTypeList";
  LOG_START();
  auto alternative_type_list =
    ProductionFactory::Get(Production::ALTERNATIVE_TYPE_LIST);
  if (alternative_type_list->Parse(asnData, asnDataIndex, endStop))
  {
    mAlternativeTypeList = alternative_type_list;
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
