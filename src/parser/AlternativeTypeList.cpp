#include "AlternativeTypeList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
AlternativeTypeList::
GetType() const
{
  return Production::ALTERNATIVE_TYPE_LIST;
}

bool
AlternativeTypeList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("AlternativeTypeList");

  // AlternativeTypeList ::=
  //   NamedType
  // | AlternativeTypeList "," NamedType

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "NamedType";
    LOG_START();
    auto named_type =
      ProductionFactory::Get(Production::NAMED_TYPE);
    if (named_type->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mNamedType.push_back(named_type);
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }

    obj = ",";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mNamedType.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
