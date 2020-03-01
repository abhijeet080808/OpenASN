#include "SignedNumber.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SignedNumber::
GetType() const
{
  return Production::SIGNED_NUMBER;
}

bool
SignedNumber::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SignedNumber");

  // SignedNumber ::=
  //       number
  // | "-" number

  size_t starting_index = asnDataIndex;

  auto obj = "Number";
  LOG_START();
  auto number =
    ProductionFactory::Get(Production::NUMBER);
  if (number->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mNumber = number;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "NegativeNumber";
  LOG_START();
  auto negative_number =
    ProductionFactory::Get(Production::NEGATIVE_NUMBER);
  if (negative_number->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mNegativeNumber = negative_number;
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
