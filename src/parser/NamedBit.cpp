#include "NamedBit.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedBit::
GetType() const
{
  return Production::NAMED_BIT;
}

bool
NamedBit::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // NamedBit ::=
  //   identifier "(" number ")"
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

  obj = "Number";
  LOG_START();
  auto number =
    ProductionFactory::Get(Production::NUMBER);
  if (number->Parse(asnData, asnDataIndex, endStop))
  {
    mNumber = number;
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

  // identifier "(" DefinedValue ")"

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
