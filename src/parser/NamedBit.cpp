#include "NamedBit.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NamedBit ::=
  //   identifier "(" number ")"
  // | identifier "(" DefinedValue ")"

  LOG_START("Identifier", asnData);
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, endStop))
  {
    mIdentifier = identifier;
    LOG_PASS("Identifier", asnData);
  }
  else
  {
    LOG_FAIL("Identifier", asnData);
    return false;
  }

  LOG_START("(", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "(")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("(", asnData);
  }
  else
  {
    LOG_FAIL("(", asnData);
    return false;
  }

  LOG_START("Number", asnData);
  auto number =
    ProductionFactory::Get(Production::NUMBER);
  if (number->Parse(asnData, endStop))
  {
    mNumber = number;
    LOG_PASS("Number", asnData);
  }
  else
  {
    LOG_FAIL("Number", asnData);
    return false;
  }

  LOG_START(")", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == ")")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS(")", asnData);
  }
  else
  {
    LOG_FAIL(")", asnData);
    return false;
  }

  // identifier "(" DefinedValue ")"

  return true;
}
