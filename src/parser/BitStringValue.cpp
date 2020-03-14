#include "BitStringValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BitStringValue::
GetType() const
{
  return Production::BIT_STRING_VALUE;
}

bool
BitStringValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("BitStringValue");

  // BitStringValue ::=
  //   bstring
  // | hstring
  // | "{" IdentifierList "}"
  // | "{" "}"
  // | CONTAINING Value

  size_t starting_index = asnDataIndex;

  auto obj = "Bstring";
  LOG_START();
  auto bstring =
    ProductionFactory::Get(Production::BSTRING);
  if (bstring->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mBstring = bstring;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Hstring";
  LOG_START();
  auto hstring =
    ProductionFactory::Get(Production::HSTRING);
  if (hstring->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mHstring = hstring;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "{";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();

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
      LOG_FAIL();

      endStop.push_back("}");

      obj = "IdentifierList";
      LOG_START();
      auto identifier_list =
        ProductionFactory::Get(Production::IDENTIFIER_LIST);
      if (identifier_list->Parse(asnData, asnDataIndex, endStop, parsePath))
      {
        endStop.pop_back();
        mIdentifierList = identifier_list;
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
  }
  else
  {
    LOG_FAIL();
  }

  obj = "CONTAINING";
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

  obj = "Value";
  LOG_START();
  auto value =
    ProductionFactory::Get(Production::VALUE);
  if (value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mValue = value;
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
