#include "NamedBitList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedBitList::
GetType() const
{
  return Production::NAMED_BIT_LIST;
}

bool
NamedBitList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("NamedBitList");

  // NamedBitList ::=
  //   NamedBit
  // | NamedBitList "," NamedBit

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "NamedBit";
    LOG_START();
    auto named_bit =
      ProductionFactory::Get(Production::NAMED_BIT);
    if (named_bit->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mNamedBit.push_back(named_bit);
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

  if (mNamedBit.empty())
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
