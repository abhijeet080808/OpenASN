#include "SignedNumber.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // SignedNumber ::=
  //       number
  // | "-" number

  LOG_START("Number", asnData);
  auto number =
    ProductionFactory::Get(Production::NUMBER);
  if (number->Parse(asnData, endStop))
  {
    mNumber = number;
    LOG_PASS("Number", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("Number", asnData);
  }

  LOG_START("NegativeNumber", asnData);
  auto negative_number =
    ProductionFactory::Get(Production::NEGATIVE_NUMBER);
  if (negative_number->Parse(asnData, endStop))
  {
    mNegativeNumber = negative_number;
    LOG_PASS("NegativeNumber", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NegativeNumber", asnData);
  }

  return false;
}
