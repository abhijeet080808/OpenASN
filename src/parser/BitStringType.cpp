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
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("BitStringType");

  // BitStringType ::=
  //   BIT STRING
  // | BIT STRING "{" NamedBitList "}"

  size_t starting_index = asnDataIndex;

  auto obj = "BIT";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "STRING";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "{";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }

  endStop.push_back("}");

  obj = "NamedBitList";
  LOG_START();
  auto named_bit_list =
    ProductionFactory::Get(Production::NAMED_BIT_LIST);
  if (named_bit_list->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    endStop.pop_back();
    mNamedBitList = named_bit_list;
    LOG_PASS();
  }
  else
  {
    endStop.pop_back();
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
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
