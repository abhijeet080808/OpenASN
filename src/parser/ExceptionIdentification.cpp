#include "ExceptionIdentification.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ExceptionIdentification::
GetType() const
{
  return Production::EXCEPTION_IDENTIFICATION;
}

bool
ExceptionIdentification::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ExceptionIdentification ::=
  //   SignedNumber
  // | DefinedValue
  // | Type ":" Value

  size_t starting_index = asnDataIndex;

  auto obj = "SignedNumber";
  LOG_START();
  auto signed_number =
    ProductionFactory::Get(Production::SIGNED_NUMBER);
  if (signed_number->Parse(asnData, asnDataIndex, endStop))
  {
    mSignedNumber = signed_number;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "DefinedValue";
  LOG_START();
  auto defined_value =
    ProductionFactory::Get(Production::DEFINED_VALUE);
  if (defined_value->Parse(asnData, asnDataIndex, endStop))
  {
    mDefinedValue = defined_value;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Type";
  LOG_START();
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop))
  {
    mType = type;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }

  obj = ":";
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
    return false;
  }

  obj = "Value";
  LOG_START();
  auto value =
    ProductionFactory::Get(Production::VALUE);
  if (value->Parse(asnData, asnDataIndex, endStop))
  {
    mValue = value;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
