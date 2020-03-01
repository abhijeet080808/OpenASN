#include "NamedNumber.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedNumber::
GetType() const
{
  return Production::NAMED_NUMBER;
}

bool
NamedNumber::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("NamedNumber");

  // NamedNumber ::=
  //   identifier "(" SignedNumber ")"
  // | identifier "(" DefinedValue ")"

  size_t starting_index = asnDataIndex;

  auto obj = "Identifier";
  LOG_START();
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mIdentifier = identifier;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "(";
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

  endStop.push_back(")");

  obj = "SignedNumber";
  LOG_START();
  auto signed_number =
    ProductionFactory::Get(Production::SIGNED_NUMBER);
  if (signed_number->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSignedNumber = signed_number;
    endStop.pop_back();
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  if (!mSignedNumber)
  {
    obj = "DefinedValue";
    LOG_START();
    auto defined_value =
      ProductionFactory::Get(Production::DEFINED_VALUE);
    if (defined_value->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mDefinedValue = defined_value;
      endStop.pop_back();
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
  }

  obj = ")";
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
