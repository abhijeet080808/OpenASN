#include "RootAlternativeTypeList.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // RootAlternativeTypeList ::= AlternativeTypeList

  LOG_START("AlternativeTypeList", asnData);
  auto alternative_type_list =
    ProductionFactory::Get(Production::ALTERNATIVE_TYPE_LIST);
  if (alternative_type_list->Parse(asnData, endStop))
  {
    mAlternativeTypeList = alternative_type_list;
    LOG_PASS("AlternativeTypeList", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("AlternativeTypeList", asnData);
    return false;
  }
}
