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
      std::vector<std::string>& endStop)
{
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
    if (named_type->Parse(asnData, asnDataIndex, endStop))
    {
      mNamedType.push_back(named_type);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      asnDataIndex = starting_index;
      return false;
    }

    obj = ",";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      LOG_PASS();
      ++asnDataIndex;
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
    return false;
  }
  else
  {
    return true;
  }
}
