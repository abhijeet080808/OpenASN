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
      std::vector<std::string>& endStop)
{
  // NamedNumber ::=
  //   identifier "(" SignedNumber ")"
  // | identifier "(" DefinedValue ")"

  size_t starting_index = asnDataIndex;

  auto obj = "Identifier";
  LOG_START();
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, asnDataIndex, endStop))
  {
    mIdentifier = identifier;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "(";
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

  endStop.push_back(")");

  obj = "SignedNumber";
  LOG_START();
  auto signed_number =
    ProductionFactory::Get(Production::SIGNED_NUMBER);
  if (signed_number->Parse(asnData, asnDataIndex, endStop))
  {
    mSignedNumber = signed_number;
    LOG_PASS();
    endStop.pop_back();
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
    if (defined_value->Parse(asnData, asnDataIndex, endStop))
    {
      mDefinedValue = defined_value;
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
  }

  obj = ")";
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
