#include "IntegerValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IntegerValue::
GetType() const
{
  return Production::INTEGER_VALUE;
}

bool
IntegerValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("IntegerValue");

  // IntegerValue ::= SignedNumber | identifier

  size_t starting_index = asnDataIndex;

  auto obj = "SignedNumber";
  LOG_START();
  auto signed_number =
    ProductionFactory::Get(Production::SIGNED_NUMBER);
  if (signed_number->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSignedNumber = signed_number;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Identifier";
  LOG_START();
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mIdentifier = identifier;
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
