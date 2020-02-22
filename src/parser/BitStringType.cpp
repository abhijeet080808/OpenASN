#include "BitStringType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BitStringType::
GetType() const
{
  return Production::BIT_STRING_TYPE;
}

bool
BitStringType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // BitStringType ::=
  //   BIT STRING
  // | BIT STRING "{" NamedBitList "}"

  size_t starting_index = asnDataIndex;

  auto obj = "BIT";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "STRING";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "{";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    return true;
  }

  endStop.push_back("}");

  obj = "NamedBitList";
  LOG_START();
  auto named_bit_list =
    ProductionFactory::Get(Production::NAMED_BIT_LIST);
  if (named_bit_list->Parse(asnData, asnDataIndex, endStop))
  {
    mNamedBitList = named_bit_list;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
