#include "NamedNumber.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NamedNumber ::=
  //   identifier "(" SignedNumber ")"
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

  LOG_START("SignedNumber", asnData);
  auto signed_number =
    ProductionFactory::Get(Production::SIGNED_NUMBER);
  if (signed_number->Parse(asnData, endStop))
  {
    mSignedNumber = signed_number;
    LOG_PASS("SignedNumber", asnData);
  }
  else
  {
    LOG_FAIL("SignedNumber", asnData);
    return false;
#if 0
    LOG_START("DefinedValue", asnData);
    auto defined_value =
      ProductionFactory::Get(Production::DEFINED_VALUE);
    if (defined_value->Parse(asnData, endStop))
    {
      mDefinedValue = defined_value;
      LOG_PASS("DefinedValue", asnData);
    }
    else
    {
      LOG_FAIL("DefinedValue", asnData);
      return false;
    }
#endif
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

  return true;
}
