#include "ClassNumber.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ClassNumber::
GetType() const
{
  return Production::CLASS_NUMBER;
}

bool
ClassNumber::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ClassNumber ::=
  //   number
  // | DefinedValue

  size_t starting_index = asnDataIndex;

  auto obj = "Number";
  LOG_START();
  auto number =
    ProductionFactory::Get(Production::NUMBER);
  if (number->Parse(asnData, asnDataIndex, endStop))
  {
    mNumber = number;
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
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
