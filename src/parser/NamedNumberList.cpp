#include "NamedNumberList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedNumberList::
GetType() const
{
  return Production::NAMED_NUMBER_LIST;
}

bool
NamedNumberList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // NamedNumberList ::=
  //   NamedNumber
  // | NamedNumberList "," NamedNumber

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "NamedNumber";
    LOG_START();
    auto named_number =
      ProductionFactory::Get(Production::NAMED_NUMBER);
    if (named_number->Parse(asnData, asnDataIndex, endStop))
    {
      mNamedNumber.push_back(named_number);
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

  if (mNamedNumber.empty())
  {
    asnDataIndex = starting_index;
    return false;
  }
  else
  {
    return true;
  }
}
