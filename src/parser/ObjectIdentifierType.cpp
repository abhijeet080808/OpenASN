#include "ObjectIdentifierType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ObjectIdentifierType::
GetType() const
{
  return Production::OBJECT_IDENTIFIER_TYPE;
}

bool
ObjectIdentifierType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // ObjectIdentifierType ::= OBJECT IDENTIFIER

  LOG_START("OBJECT", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "OBJECT")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("OBJECT", asnData);
  }
  else
  {
    LOG_FAIL("OBJECT", asnData);
    return false;
  }

  LOG_START("IDENTIFIER", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "IDENTIFIER")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("IDENTIFIER", asnData);
  }
  else
  {
    LOG_FAIL("IDENTIFIER", asnData);
    return false;
  }

  return true;
}
